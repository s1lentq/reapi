package versioning

import groovy.transform.CompileStatic
import groovy.transform.ToString
import groovy.transform.TypeChecked
import org.joda.time.DateTime

@CompileStatic @TypeChecked
@ToString(includeNames = true)
class ReapiVersionInfo {
	int majorVersion
	int minorVersion
	Integer maintenanceVersion
	String specialVersion
	Integer countCommit
	DateTime lastCommitDate

	String format(String versionSeparator, String suffixSeparator, boolean includeSuffix) {
		StringBuilder sb = new StringBuilder()
		sb.append(majorVersion).append(versionSeparator).append(minorVersion)
		if (maintenanceVersion != null) {
			sb.append(versionSeparator).append(maintenanceVersion)
		}

		if (specialVersion && includeSuffix) {
			sb.append(suffixSeparator).append(specialVersion)
		}

		return sb.toString()
	}
	String asVersion() {
		if (specialVersion.length() > 0) {
			sprintf("%d.%d.%d-%s", majorVersion, minorVersion, countCommit, specialVersion)
		}
		else
			sprintf("%d.%d.%d", majorVersion, minorVersion, countCommit)
	}
	String asMavenVersion() {
		format('.', '-', true)
	}
}
