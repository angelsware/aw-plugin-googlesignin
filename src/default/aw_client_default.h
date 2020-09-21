#ifndef __AW_GOOGLE_SIGN_IN_CLIENT_DEFAULT_H__
#define __AW_GOOGLE_SIGN_IN_CLIENT_DEFAULT_H__

#include <googlesignin/aw_client.h>
#include <googlesignin/aw_signinoptions.h>

namespace GoogleSignIn {
	class IClientListener;

	class CClient_Default
		: public IClient
	{
	private:
		void addListener(IClientListener* listener) override {}
		void removeListener(IClientListener* listener) override {}
		void clearAllListeners() override {}
		void trySilentSignIn() override {}
		void signIn() override {}
		void logOut() override {}
	};
}

#endif
