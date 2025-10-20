#include "fakebook.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define initialCapacity 5

// make a new network and set it up
Network *createNetwork(){
    Network *net = malloc(sizeof(Network));
    net->users =  malloc(sizeof(User) * initialCapacity); 
    net->numUsers = 0;
    net->capacity = initialCapacity;
    return net;
}

// make a new user and add basic info
User *createUser(Network *net, const char *name){
    User * newUser = malloc(sizeof(User));
    newUser->friendCapacity = net->capacity;
    strcpy(newUser->name,name);
    newUser->friends = malloc(sizeof(User) * net->capacity);
    newUser->id = net->numUsers + 1;
    newUser->numFriends = 0;
    newUser->posts = NULL;
}

// connect two users together as friends
void addFriend(User *u1, User *u2){
    u1->friends[u1->numFriends + 1] = u2;
    u2->friends[u2->numFriends + 1] = u1;
}

// make a new post for a user
void addPost(User *user, const char *content){
    Post *newPost = malloc(sizeof(Post));
    newPost->content = malloc(strlen(content) + 1);
    strcpy(newPost->content, content);
    int post_count = 1;
    newPost->id = post_count;
    post_count++;
    newPost->next = user->posts->next;
    user->posts = newPost;
}

// show all of a user’s friends
void showFriends(User *user){
    if(user->numFriends == 0){
        printf("No friends yet, but you got it!");
    }
    int i = user->numFriends - 1;
    printf("Friends list: ");
    while(i >= 0){
        printf("%s, ", user->friends[i]->name);
        i--;
    }
}

// show all posts for a user
void showFeed(User *user){
    if(user->posts == NULL){
        printf("No posts to show");
    }
    else{
        printf("Posts list: ");
        Post *current = user->posts;
        while(current != NULL){
            printf("%d - %s\n",user->posts->id, user->posts->content);
            current = user->posts->next;
        }
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



