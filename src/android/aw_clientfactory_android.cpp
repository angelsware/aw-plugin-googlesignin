#include <googlesignin/aw_clientfactory.h>
#include "aw_client_android.h"

namespace GoogleSignIn {
	IClient* CClientFactory::create(const char* clientId, ESignInOptions signInOptions) {
		return new CClient_Android(clientId, signInOptions);
	}

	void CClientFactory::destroy(IClient* client) {
		delete client;
	}
}
