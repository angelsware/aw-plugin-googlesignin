#include <googlesignin/aw_clientfactory.h>
#include "aw_client_default.h"

namespace GoogleSignIn {
	IClient* CClientFactory::create(const char* clientId, ESignInOptions signInOptions) {
		return new CClient_Default();
	}

	void CClientFactory::destroy(IClient* client) {
		delete client;
	}
}
