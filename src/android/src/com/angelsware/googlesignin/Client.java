package com.angelsware.googlesignin;

import android.content.Intent;

import androidx.annotation.NonNull;

import com.angelsware.engine.ActivityResultListener;
import com.angelsware.engine.AppActivity;
import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;

public class Client implements ActivityResultListener {
	private GoogleSignInClient mGoogleSignInClient;
	private final int RC_SIGN_IN = 9001;

	private static native void onSignInSuccess(String displayName, String email, String idToken);
	private static native void onSignInFailed();

	public void create(String clientId, long signInOptions) {
		AppActivity appActivity = (AppActivity)AppActivity.getActivity();
		appActivity.addActivityResultListener(this);

		// TODO: Handle signInOptions.
		GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
				.requestIdToken(clientId)
				.requestEmail()
				.build();

		mGoogleSignInClient = GoogleSignIn.getClient(AppActivity.getActivity(), gso);
	}

	public void destroy() {
		AppActivity appActivity = (AppActivity)AppActivity.getActivity();
		appActivity.removeActivityResultListener(this);
	}

	public void trySilentSignIn() {
		mGoogleSignInClient.silentSignIn().addOnCompleteListener(new OnCompleteListener<GoogleSignInAccount>() {
			@Override
			public void onComplete(@NonNull Task<GoogleSignInAccount> task) {
				handleSignIn(task);
			}
		});
	}

	public void signIn() {
		Intent signInIntent = mGoogleSignInClient.getSignInIntent();
		AppActivity.getActivity().startActivityForResult(signInIntent, RC_SIGN_IN);
	}

	public void logOut() {
		mGoogleSignInClient.signOut();
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == RC_SIGN_IN) {
			handleSignIn(GoogleSignIn.getSignedInAccountFromIntent(data));
		}
	}

	private void handleSignIn(Task<GoogleSignInAccount> task) {
		try {
			GoogleSignInAccount account = task.getResult(ApiException.class);
			if (account != null) {
				String displayName;
				if (account.getDisplayName() != null) {
					displayName = account.getDisplayName();
				} else {
					displayName = "";
				}
				onSignInSuccess(displayName, account.getEmail(), account.getIdToken());
			} else {
				onSignInFailed();
			}
		} catch (ApiException e) {
			e.printStackTrace();
			onSignInFailed();
		}
	}
}
