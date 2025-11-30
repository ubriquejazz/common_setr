// condition_flag.c

osMutexId myMutexHandle;

CondFlag_T* CondFlag_Create() {
    CondFlag_T* new_flag = (CondFlag_T*)malloc(sizeof(CondFlag_T));
    if (new_flag) {
        new_flag->state = CF_Reset;
        // pthread_mutex_init(&new_flag->mutex, NULL);
        // pthread_cond_init(&new_flag->condition_var, NULL); 
    }
    return new_flag;
}

void CondFlag_Set(CondFlag_T* flag_handle) {
    if (flag_handle) {
        osMutexWait(myMutexHandle, osWaitForever);
        flag_handle->state = CF_Set;
        osMutexRelease(myMutexHandle);
    }
}

void CondFlag_Clear(CondFlag_T* flag_handle) {
    if (flag_handle) {
        osMutexWait(myMutexHandle, osWaitForever);
        flag_handle->state = CF_Set;
        osMutexRelease(myMutexHandle);
    }
}

bool CondFlag_Check(const CondFlag_T* flag_handle) {
    bool result = false;
    if (flag_handle) {
        osMutexWait(myMutexHandle, osWaitForever);
        result = (flag_handle->state == CF_Set);
        osMutexRelease(myMutexHandle);
    }
    return result;
}