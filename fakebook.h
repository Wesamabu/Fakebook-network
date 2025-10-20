#ifndef FAKEBOOK_H
#define FAKEBOOK_H

typedef struct Post {
    int id;
    char *content;
    struct Post *next;  // linked list of posts
} Post;
 
typedef struct User {
    int id;
    char name[50]; 
    struct User **friends;   // dynamic array of User* (adjacency list)
    int numFriends;
    int friendCapacity;
    Post *posts;             // linked list of posts
} User;
 
typedef struct Network {
    User **users;            // dynamic array of all users
    int numUsers;
    int capacity;
} Network;

Network *createNetwork();
User *createUser(Network *net, const char *name);
void addFriend(User *u1, User *u2);
void addPost(User *user, const char *content);
void showFriends(User *user);
void showFeed(User *user);
void suggestFriends(User *user);
void displayNetwork(Network *net);
void freeNetwork(Network *net);

#endif