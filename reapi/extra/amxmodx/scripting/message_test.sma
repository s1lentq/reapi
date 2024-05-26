#include <amxmodx>
#include <reapi>

public plugin_init()
{
	register_plugin("ReAPI MessageHook Test", "1.0", "s1lent");
	RegisterMessage(get_user_msgid("SayText"), "MessageSayText_Pre",  .post = false);
	RegisterMessage(get_user_msgid("SayText"), "MessageSayText_Post", .post = true);
}

/**
* Destination types for message hook
*/
new const g_MsgDestination[][] =
{
	"MSG_BROADCAST",		// Unreliable to all
	"MSG_ONE",				// Reliable to one (msg_entity)
	"MSG_ALL",				// Reliable to all
	"MSG_INIT",				// Write to the init string
	"MSG_PVS",				// Ents in PVS of org
	"MSG_PAS",				// Ents in PAS of org
	"MSG_PVS_R",			// Reliable to PVS
	"MSG_PAS_R",			// Reliable to PAS
	"MSG_ONE_UNRELIABLE",	// Send to one client, but don't put in reliable stream, put in unreliable datagram (could be dropped)
	"MSG_SPEC"				// Sends to all spectator proxies
};

/**
* Message argument types used with GetMessageArgType()
*/
new const g_MsgArgType[][] =
{
	"Byte",
	"Char",
	"Short",
	"Long",
	"Angle",
	"Coord",
	"String",
	"Entity",
};

/**
* Blocking behavior types for messages used with SetMessageBlock()/GetMessageBlock()
*/
new const g_MsgBlockType[][] =
{
	"MSG_BLOCK_NOT",  // Not a block
	"MSG_BLOCK_ONCE", // Block once
	"MSG_BLOCK_SET"   // Set block
};

public MessageSayText_Pre(const msg_id, const msg_dest, const id)
{
	server_print("^nMessageSayText_Pre");

	DumpMessageArgs(msg_id);

	static bool:recursive_guard = false;
	if (!recursive_guard)
	{
		recursive_guard = true; // avoid deadlock

		// Modify original text message in chat
		SetMessageData(MsgDest, MSG_ALL); // send text messages in the chat to everyone
		SetMessageData(MsgTargetId, NULLENT);
		SetMessageData(MsgArg, 2, "^4(Test) ^3%s1^1 @ ^4%s3^1 :  %s2"); // change format

		if (is_user_connected(id))
		{
			// Send another chat message, test deadlock
			new szPlayerName[32];
			get_user_name(id, szPlayerName, charsmax(szPlayerName));

			new szTextMsg[256];
			GetMessageData(MsgArg, 4, szTextMsg, charsmax(szTextMsg));

			message_begin(MSG_ONE, msg_id, .player = id);
			write_byte(id);
			write_string("^3%s1^1 @ ^4%s3^1 : %s2");
			write_string(szPlayerName);
			write_string(szTextMsg);
			write_string("Courtyard");
			message_end();

			// Send another text message, but on screen in center
			message_begin(MSG_ONE, get_user_msgid("TextMsg"), .player = id);
			write_byte(print_center);

			for (new i = 1; i <= GetMessageArgsNum(); i++)
			{
				new MsgArgType:type = GetMessageArgType(i);
				if (type == ArgString)
				{
					new szBuffer[256];
					GetMessageOrigData(MsgArg, i, szBuffer, charsmax(szBuffer));
					write_string(szBuffer);
				}
			}

			message_end();
		}

		recursive_guard = false;
	}
}

public MessageSayText_Post(const msg_id, const msg_dest, const id)
{
	server_print("^nMessageSayText_Post");
	DumpMessageArgs(msg_id);
}

stock Float:fabs(Float:x)
{
	return x > 0 ? x : -x;
}

stock DumpMessageArgs(const msg_id)
{
	// indicates that the message data has been modified
	new const symbolIndicateModified[] = "+";

	if (IsMessageDataModified(MsgDest))
		server_print("Dest                  = %s (%d) > changed to > %s (%d)", g_MsgDestination[GetMessageOrigData(MsgDest)], GetMessageOrigData(MsgDest), g_MsgDestination[GetMessageData(MsgDest)], GetMessageData(MsgDest));
	else
		server_print("Dest                  = %s (%d)", g_MsgDestination[GetMessageData(MsgDest)], GetMessageData(MsgDest));

	new Float:vecOrigin[3];
	GetMessageData(MsgOrigin, vecOrigin);

	if (IsMessageDataModified(MsgOrigin))
	{
		new Float:vecSourceOrigin[3];
		GetMessageOrigData(MsgOrigin, vecSourceOrigin);
		server_print("Origin                = (%0.2f, %0.2f, %0.2f) > changed to > (%0.2f, %0.2f, %0.2f)", vecSourceOrigin[0], vecSourceOrigin[1], vecSourceOrigin[2], vecOrigin[0], vecOrigin[1], vecOrigin[2]);
	}
	else
	{
		server_print("Origin                = (%0.2f, %0.2f, %0.2f)", vecOrigin[0], vecOrigin[1], vecOrigin[2]);
	}

	if (IsMessageDataModified(MsgTargetId))
		server_print("Receiver              = %d > changed to > %d", GetMessageOrigData(MsgTargetId), GetMessageData(MsgTargetId));
	else
		server_print("Receiver              = %d", GetMessageData(MsgTargetId));

	server_print("Block state           = %s", g_MsgBlockType[any:GetMessageBlock(msg_id)]);
	server_print("Args count            = %d", GetMessageArgsNum());
	server_print("Message modified      %s", IsMessageDataModified() ? symbolIndicateModified : "-");

	// Iterate over all arguments of current message
	for (new i = 1; i <= GetMessageArgsNum(); i++)
	{
		new MsgArgType:type = GetMessageArgType(i);
		new bool:isModified = IsMessageDataModified(MsgArg, i);

		// Print string values of argument
		if (type == ArgString)
		{
			new curString[256], origString[256];
			GetMessageData(MsgArg, i, curString, charsmax(curString));
			GetMessageOrigData(MsgArg, i, origString, charsmax(origString));

			replace_all(curString, charsmax(curString), "^n", "");
			replace_all(origString, charsmax(origString), "^n", "");

			if (!equal(origString, curString) || isModified)
			{
				server_print("     %-2d %-13s %s ^"%s^" > changed to > ^"%s^"", i, g_MsgArgType[any:type], isModified ? symbolIndicateModified : "-", origString, curString);
			}
			else
			{
				server_print("     %-2d %-13s %s ^"%s^"", i, g_MsgArgType[any:type], isModified ? symbolIndicateModified : "-", curString);
			}
		}
		// Print float point values of argument
		else if (type == ArgAngle || type == ArgCoord)
		{
			new Float:flCurValue  = Float:GetMessageData(MsgArg, i);
			new Float:flOrigValue = Float:GetMessageOrigData(MsgArg, i);

			if (fabs(flCurValue - flOrigValue) > 0.1 || isModified)
			{
				server_print("     %-2d %-13s %s ^"%f^" > changed to > ^"%f^"", i, g_MsgArgType[any:type], isModified ? symbolIndicateModified : "-", flOrigValue, flCurValue);
			}
			else
			{
				server_print("     %-2d %-13s %s ^"%f^"", i, g_MsgArgType[any:type], isModified ? symbolIndicateModified : "-", flCurValue);
			}
		}
		// Print integer values of argument
		else
		{
			new iCurValue  = GetMessageData(MsgArg, i);
			new iOrigValue = GetMessageOrigData(MsgArg, i);

			if (iCurValue != iOrigValue || isModified)
			{
				server_print("     %-2d %-13s %s ^"%i^" > changed to > ^"%i^"", i, g_MsgArgType[any:type], isModified ? symbolIndicateModified : "-", iOrigValue, iCurValue);
			}
			else
			{
				server_print("     %-2d %-13s %s ^"%i^"", i, g_MsgArgType[any:type], isModified ? symbolIndicateModified : "-", iCurValue);
			}
		}
	}

	server_print("^n");
}
