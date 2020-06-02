#include "aw_client_android.h"
#include <googlesignin/aw_clientlistener.h>
#include <platform/android/aw_jniclass.h>
#include <platform/android/aw_jni.h>
#include <platform/android/aw_jninativestring.h>
#include <platform/android/aw_jnistring.h>
#include <type/aw_vector.h>

static Type::CVector<GoogleSignIn::IClientListener*> sListeners;

JNIEXPORT void JNICALL Java_com_angelsware_googlesignin_Client_onSignInSuccess(JNIEnv* env, jclass clazz, jstring displayName, jstring email, jstring idToken) {
	Platform::CJniNativeString displayNameStr(displayName);
	Platform::CJniNativeString emailStr(email);
	Platform::CJniNativeString idTokenStr(idToken);
	for (unsigned int i = 0; i < sListeners.getSize(); ++i) {
		sListeners[i]->onGoogleSignInSuccess(displayNameStr.getText(), emailStr.getText(), idTokenStr.getText());
	}
}

JNIEXPORT void JNICALL Java_com_angelsware_googlesignin_Client_onSignInFailed(JNIEnv* env, jclass clazz) {
	for (unsigned int i = 0; i < sListeners.getSize(); ++i) {
		sListeners[i]->onGoogleSignInFailed();
	}
}

namespace GoogleSignIn {
	CClient_Android::CClient_Android(const char* clientId, ESignInOptions signInOptions) {
		mClient = new Platform::CJniClass("com/angelsware/googlesignin/Client", "()V");
		Platform::CJniString jniClientId(clientId);
		mClient->callVoidMethod("create", "(Ljava/lang/String;J)V", jniClientId.getText(), static_cast<jlong>(signInOptions));
	}

	CClient_Android::~CClient_Android() {
		mClient->callVoidMethod("destroy", "()V");
		delete mClient;
	}

	void CClient_Android::addListener(IClientListener* listener) {
		sListeners.pushBack(listener);
	}

	void CClient_Android::removeListener(IClientListener* listener) {
		for (unsigned int i = 0; i < sListeners.getSize(); ++i) {
			if (sListeners[i] == listener) {
				sListeners.eraseAndReplaceWithLast(i);
				break;
			}
		}
	}

	void CClient_Android::clearAllListeners() {
		sListeners.clear();
	}

	void CClient_Android::trySilentSignIn() {
		mClient->callVoidMethod("trySilentSignIn", "()V");
	}

	void CClient_Android::signIn() {
		mClient->callVoidMethod("signIn", "()V");
	}

	void CClient_Android::logOut() {
		mClient->callVoidMethod("logOut", "()V");
	}
}
