#ifndef __AW_GOOGLE_SIGN_IN_CLIENT_H__
#define __AW_GOOGLE_SIGN_IN_CLIENT_H__

#include <googlesignin/aw_signinoptions.h>

namespace GoogleSignIn {
	class IClientListener;

	class IClient
	{
	public:
		virtual ~IClient() {}

		virtual void addListener(IClientListener* listener) = 0;
		virtual void removeListener(IClientListener* listener) = 0;
		virtual void clearAllListeners() = 0;
		virtual void trySilentSignIn() = 0;
		virtual void signIn() = 0;
		virtual void logOut() = 0;
	};
}

#endif
