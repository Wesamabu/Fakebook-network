#include "fakebook.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Network *net = createNetwork();
    int choice;
    char name[50];
    char content[200];
    int id1, id2;
    printf("==== Welcome to Fakebook ====\n");
    while(1) {
        printf("\n1. Add new user");
        printf("\n2. Add friendship");
        printf("\n3. Create post");
        printf("\n4. Show user's friends");
        printf("\n5. Show user's feed");
        printf("\n6. Suggest friends");
        printf("\n7. Display entire network");
        printf("\n8. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline
        switch (choice) {
            case 1:
                printf("Enter name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                net->users[net->numUsers++] = createUser(net, name);
                printf("User '%s' created with ID %d!\n", name, net->numUsers);
                break;
            case 2:
                printf("Enter first user ID: ");
                scanf("%d", &id1);
                printf("Enter second user ID: ");
                scanf("%d", &id2);
                if (id1 <= net->numUsers && id2 <= net->numUsers && id1 != id2) {
                    addFriend(net->users[id1 - 1], net->users[id2 - 1]);
                    printf("%s and %s are now friends!\n",
                           net->users[id1 - 1]->name,
                           net->users[id2 - 1]->name);
                } else {
                    printf("Invalid IDs.\n");
                }
                break;
            case 3:
                printf("Enter user ID: ");
                scanf("%d", &id1);
                getchar();
                printf("Enter post content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';
                addPost(net->users[id1 - 1], content);
                printf("Post added for %s!\n", net->users[id1 - 1]->name);
                break;
            case 4:
                printf("Enter user ID: ");
                scanf("%d", &id1);
                showFriends(net->users[id1 - 1]);
                break;
            case 5:
                printf("Enter user ID: ");
                scanf("%d", &id1);
                showFeed(net->users[id1 - 1]);
                break;
            case 6:
                printf("Enter user ID: ");
                scanf("%d", &id1);
                suggestFriends(net->users[id1 - 1]);
                break;
            case 7:
                displayNetwork(net);
                break;
            case 8:
                printf("Goodbye!\n");
                freeNetwork(net);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}
