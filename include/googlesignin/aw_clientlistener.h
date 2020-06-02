#ifndef __AW_GOOGLE_SIGN_IN_CLIENT_LISTENER_H__
#define __AW_GOOGLE_SIGN_IN_CLIENT_LISTENER_H__

namespace GoogleSignIn {
	class IClientListener
	{
	public:
		virtual void onGoogleSignInSuccess(const char* displayName, const char* email, const char* idToken) = 0;
		virtual void onGoogleSignInFailed() = 0;

	protected:
		virtual ~IClientListener() {}
	};
}

#endif
