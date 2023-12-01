#define PHP_SCRIPT "<?php\
$height = (float)$argv[0] / 100;\
$weight = $argv[1];\
$bmi = round($weight / ($height * $height));\
if ($bmi < 16) {\
echo \"Выраженный дефицит веса\";\
} elseif ($bmi >= 16 && $bmi <= 17.9) {\
echo \"Недостаток массы тела\";\
} elseif ($bmi >= 18 && $bmi <= 24.9) {\
echo \"Норма\";\
} elseif ($bmi >= 25 && $bmi <= 29.9) {\
echo \"Чрезмерная масса тела (предожирение)\";\
} elseif ($bmi >= 30 && $bmi <= 34.9) {\
echo \"Ожирение I степени\";\
} elseif ($bmi >= 35 && $bmi <= 39.9) {\
echo \"Ожирение II степени\";\
} else {\
echo \"Ожирение III степени\";\
}\
?>"

#include <stdio.h>
#include <stdlib.h>
#include "ph7.h"

char *result = NULL;

static void Fatal(const char *zMsg)
{
    puts(zMsg);
    ph7_lib_shutdown();
    exit(0);
}

static int Output_Consumer(const void *pOutput, unsigned int nOutputLen, void *pUserData /* Unused */)
{
    if (result) {
        free(result);
    }
    result = (char *)malloc((nOutputLen + 1) * sizeof(char));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    sprintf(result, "%.*s", nOutputLen, (const char *)pOutput);

    return PH7_OK;
}

void releaseVM(
        ph7 *pEngine,
        ph7_vm *pVm
        ) {
    ph7_vm_release(pVm);
    ph7_release(pEngine);
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
            PHP_SCRIPT,
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

    if (height >= 1000 || weight >= 1000) {
        releaseVM(
                pEngine,
                pVm
                );
        return result;
    }

    char heightString[4];
    snprintf(heightString, sizeof(heightString), "%d", height);
    heightString[3] = 0;

    char weightString[4];
    snprintf(weightString, sizeof(weightString), "%d", weight);
    weightString[3] = 0;

    ph7_vm_config(pVm, PH7_VM_CONFIG_ARGV_ENTRY, heightString);
    ph7_vm_config(pVm, PH7_VM_CONFIG_ARGV_ENTRY, weightString);

    ph7_vm_exec(pVm, 0);

    releaseVM(
            pEngine,
            pVm
    );
    return result;
}
