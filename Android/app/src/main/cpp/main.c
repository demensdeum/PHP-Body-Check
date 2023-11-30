#define PHP_PROG "<?php "\
"echo round($argv[0] / $argv[1], 2);'"\
"?>"

#include <stdio.h>
#include <stdlib.h>
#include "ph7.h"

#include <android/log.h>
#define LOGV(TAG, message) __android_log_print(ANDROID_LOG_VERBOSE, TAG, "%s", message)

char *result = "NONE";

static void Fatal(const char *zMsg)
{
    puts(zMsg);
    ph7_lib_shutdown();
    exit(0);
}

static int Output_Consumer(const void *pOutput, unsigned int nOutputLen, void *pUserData /* Unused */)
{
    result = (char *)malloc((nOutputLen + 1) * sizeof(char));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    sprintf(result, "%.*s", nOutputLen, (const char *)pOutput);

    LOGV("PHP RESULT:", result);

    return PH7_OK;
}

const char *bodyStatus(
        int height,
        int weight
        )
{
    ph7 *pEngine;
    ph7_vm *pVm;
    int rc;

    rc = ph7_init(&pEngine);
    if (rc != PH7_OK) {
        Fatal("Error while allocating a new PH7 engine instance");
    }

    rc = ph7_compile_v2(
            pEngine,
            PHP_PROG,
            -1,
            &pVm,
            0
    );
    if (rc != PH7_OK) {
        if (rc == PH7_COMPILE_ERR) {
            const char *zErrLog;
            int nLen;
            ph7_config(pEngine,
                       PH7_CONFIG_ERR_LOG,
                       &zErrLog,
                       &nLen
            );
            if (nLen > 0) {
                puts(zErrLog);
            }
        }
        Fatal("Compile error");
    }

    rc = ph7_vm_config(pVm,
                       PH7_VM_CONFIG_OUTPUT,
                       Output_Consumer,
                       0
    );
    if (rc != PH7_OK) {
        Fatal("Error while installing the VM output consumer callback");
    }



    ph7_vm_config(pVm, PH7_VM_CONFIG_ARGV_ENTRY, "20");
    ph7_vm_config(pVm, PH7_VM_CONFIG_ARGV_ENTRY, "30");

    ph7_vm_exec(pVm, 0);

    ph7_vm_release(pVm);
    ph7_release(pEngine);
    return result;
}
