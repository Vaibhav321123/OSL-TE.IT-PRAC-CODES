#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

struct ProcessInfo {
    int max[MAX_RESOURCES];
    int allocated[MAX_RESOURCES];
    int need[MAX_RESOURCES];
};

int numProcesses, numResources;

void input(struct ProcessInfo process[], int available[]) {
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter process %d info:\n", i);
        printf("Enter Maximum Need: ");
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &process[i].max[j]);
            process[i].need[j] = process[i].max[j];
        }
        printf("Enter Allocated Resources: ");
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &process[i].allocated[j]);
            process[i].need[j] -= process[i].allocated[j];
        }
    }
    printf("Enter Available Resources: ");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }
}

bool applySafetyAlgo(struct ProcessInfo process[], int available[], int safeSequence[]) {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    int k = 0;
    for (int i = 0; i < numProcesses; i++) {
        if (finish[i]) {
            continue;
        }

        bool canAllocate = true;
        for (int j = 0; j < numResources; j++) {
            if (process[i].need[j] > work[j]) {
                canAllocate = false;
                break;
            }
        }

        if (canAllocate) {
            for (int j = 0; j < numResources; j++) {
                work[j] += process[i].allocated[j];
            }
            finish[i] = true;
            safeSequence[k++] = i;
            i = -1; // Start over
        }
    }

    return k == numProcesses;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    int available[MAX_RESOURCES];
    int safeSequence[MAX_PROCESSES];

    struct ProcessInfo process[MAX_PROCESSES];

    input(process, available);

    if (applySafetyAlgo(process, available, safeSequence)) {
        printf("System is in a SAFE State\nSafe Sequence is: ");
        for (int i = 0; i < numProcesses; i++) {
            printf("P%d ", safeSequence[i]);
        }
    } else {
        printf("System is in an UNSAFE State\n");
    }

    return 0;
}
