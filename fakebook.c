#include "fakebook.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define initialCapacity 5

// make a new network and set it up
Network *createNetwork() {
    Network *net = malloc(sizeof(Network));
    if (!net) return NULL;
    net->users = malloc(sizeof(User*) * initialCapacity);
    if (!net->users) {
        free(net);
        return NULL;
    }
    net->numUsers = 0;
    net->capacity = initialCapacity;
    return net;
}

// make a new user and add basic info
User *createUser(Network *net, const char *name) {
    User *newUser = malloc(sizeof(User));
    if (!newUser) return NULL;
    newUser->friendCapacity = net->capacity;
    newUser->friends = malloc(sizeof(User*) * newUser->friendCapacity);
    if (!newUser->friends) {
        free(newUser);
        return NULL;
    }
    newUser->id = net->numUsers + 1;
    newUser->numFriends = 0;
    newUser->posts = NULL;
    strncpy(newUser->name, name, sizeof(newUser->name) - 1);
    newUser->name[sizeof(newUser->name) - 1] = '\0';
    return newUser;
}

// Check if users are already friends or not before trying to connect
static int isAlreadyFriend(User *u, User *candidate) {
    for (int i = 0; i < u->numFriends; i++) {
        if (u->friends[i] == candidate) return 1;
    }
    return 0;
}

// connect two users together as friends
void addFriend(User *u1, User *u2) {
    if (!u1 || !u2 || u1 == u2) return;
    if (isAlreadyFriend(u1, u2) || isAlreadyFriend(u2, u1)) return;
    if (u1->numFriends >= u1->friendCapacity) return;
    if (u2->numFriends >= u2->friendCapacity) return;
    u1->friends[u1->numFriends] = u2;
    u1->numFriends++;
    u2->friends[u2->numFriends] = u1;
    u2->numFriends++;
}

// make a new post for a user
void addPost(User *user, const char *content) {
    if (!user || !content) return;
    Post *newPost = malloc(sizeof(Post));
    if (!newPost) return;
    newPost->content = malloc(strlen(content) + 1);
    if (!newPost->content) {
        free(newPost);
        return;
    }
    strcpy(newPost->content, content);
    static int post_count = 1;   // persists across calls
    newPost->id = post_count++;
    newPost->next = user->posts; // safe even if posts is NULL
    user->posts = newPost;
}


// show all of a user’s friends
void showFriends(User *user) {
    if (!user || user->numFriends == 0) {
        printf("No friends yet, but you got it!\n");
        return;
    }
    printf("Friends list: ");
    for (int i = 0; i < user->numFriends; i++) {
        printf("%s", user->friends[i]->name);
        if (i != user->numFriends - 1) printf(", ");
    }
    printf("\n");
}

// show all posts for a user
void showFeed(User *user) {
    if (!user || user->posts == NULL) {
        printf("No posts to show\n");
        return;
    }
    printf("Posts list:\n");
    Post *current = user->posts;
    while (current != NULL) {
        printf("%d - %s\n", current->id, current->content);
        current = current->next;
    }
}


// suggest new people to connect with
void suggestFriends(User *user){
    if(user->numFriends == 0){
        printf("No friends to suggest yet");
    }
    else{
        printf("People you might know:\n");
        for( int i = 0; i < user->numFriends; i++){
            for (int j = 0; j < user->friends[i]->numFriends; j++){
                User *candidate = user->friends[i]->friends[j];
                bool friends = false;
                // check if already friends
                for( int k = 0; k < user->numFriends; k++){
                    if(candidate == user->friends[k]){
                        friends = true;
                        break;
                    }
                }
                // skip yourself
                if(candidate == user){
                    continue;
                }
                // skip people you’re already friends with
                else if(friends == true){
                    continue;
                }
                // print new suggestions
                else{
                    printf("%s\n", candidate->name);
                }
            }
        }
    }
}

// show all users and their friends
void displayNetwork(Network *net){
    if(net == NULL || net->numUsers == 0){
        printf("No network to display");
    }
    else{
        for(int i = 0; i<net->numUsers; i++){
            printf("\n%s->",net->users[i]->name);
            if(net->users[i]->numFriends == 0){
                printf("No friends");
            }
            else{
                for(int k = 0; k<net->users[i]->numFriends; k++){
                    User *curr_friend = net->users[i]->friends[k];
                    printf("%s  ",curr_friend->name);
                }
            }
        }
    }
}

// free all memory that was used by the network
void freeNetwork(Network *net){
    for(int i = 0; i<net->numUsers; i++){
        int j = 0;
        // free every post for this user
        while(net->users[i]->posts!=NULL){
            Post *free_post = net->users[i]->posts;
            net->users[i]->posts = net->users[i]->posts->next;
            free(free_post->content);
            free(free_post);
        }
        // free the user’s friends and the user itself
        free(net->users[i]->friends);
        free(net->users[i]);
    }
    // free the array of users and the network itself
    free(net->users);
    free(net);
}





