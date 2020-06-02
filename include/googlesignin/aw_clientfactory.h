#ifndef __AW_GOOGLE_SIGN_IN_CLIENT_FACTORY_H__
#define __AW_GOOGLE_SIGN_IN_CLIENT_FACTORY_H__

#include <googlesignin/aw_signinoptions.h>

namespace GoogleSignIn {
	class IClient;

	class CClientFactory {
	public:
		static IClient* create(const char* clientId, ESignInOptions signInOptions);
		static void destroy(IClient *client);
	};
}

#endif
