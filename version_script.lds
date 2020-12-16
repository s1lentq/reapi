REAPI_ABI_1.0 {
	global:
		*;
	local:
		_Zn*;
		_Zd*;

		extern "C++" {	
			regfunc::*;
			*lambda*;
			_callVoidForward*;
			_callForward*;
			*std::*;
			*__cxxabi*::*;
			*__gnu_cxx::*;
			__cxa_*;
			_txnal_*;
			__dynamic_cast;
			__gxx_personality_*;
			__gcclibcxx_demangle_callback;
			*_libm_*;
			*_intel_*;
		};
};
