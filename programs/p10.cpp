#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 1024

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msg_id;
    struct msg_buffer message;

    // Generate a unique key for the message queue
    key = ftok("progfile", 65);

    // Create a message queue and get its ID
    msg_id = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;

    printf("Enter message to send to receiver: ");
    fgets(message.msg_text, MAX_MSG_SIZE, stdin);

    // Send the message
    msgsnd(msg_id, &message, sizeof(message), 0);

    printf("Data sent is: %s", message.msg_text);

    return 0;
}

