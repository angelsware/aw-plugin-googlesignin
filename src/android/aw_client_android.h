#ifndef __AW_GOOGLE_SIGN_IN_CLIENT_ANDROID_H__
#define __AW_GOOGLE_SIGN_IN_CLIENT_ANDROID_H__

#include <googlesignin/aw_client.h>
#include <googlesignin/aw_signinoptions.h>

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL Java_com_angelsware_googlesignin_Client_onSignInSuccess(JNIEnv* env, jclass clazz, jstring displayName, jstring email, jstring idToken);
	JNIEXPORT void JNICALL Java_com_angelsware_googlesignin_Client_onSignInFailed(JNIEnv* env, jclass clazz);
#ifdef __cplusplus
}
#endif

namespace Platform {
	class CJniClass;
}

namespace GoogleSignIn {
	class CClient_Android
		: public IClient
	{
	public:
		CClient_Android(const char* clientId, ESignInOptions signInOptions);
		~CClient_Android();

	private:
		// IClient
		void addListener(IClientListener* listener) override;
		void removeListener(IClientListener* listener) override;
		void clearAllListeners() override;
		void trySilentSignIn() override;
		void signIn() override;
		void logOut() override;

		Platform::CJniClass* mClient;
	};
}

#endif
