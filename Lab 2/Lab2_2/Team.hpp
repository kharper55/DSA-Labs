#ifndef TEAM_HPP
#define TEAM_HPP

#include "ArrayStack.hpp"
#include "TeamMember.hpp"

// Note: Since prior implementation of ArrayStack does not make all indices
//       accessible, it makes more sense to create a new data structure
//       which does not inherit from the ArrayStack class.

class Team /*: public ArrayStack<TeamMember*>*/ {
    const static int DEF_CAPACITY = 64;       // default stack capacity
    public:
        Team(const int cap = DEF_CAPACITY, const string name = "Default Team");        // Constructor
        ~Team();                             // Destructor (not sure if actually needed)
        void vPush(const std::string& name); // Push Varsity member to Varsity stack
        void vPop();            // Pop Varsity member from Varsity stack
        TeamMember vTop();      // Get Varsity top member
        int vSize();            // Get Varsity squad size
        bool vEmpty();          // Is Varsity squad empty?
        void jvPush(const std::string& name); // Push JV member to JV stack
        void jvPop();           // Pop JV member from JV stack
        TeamMember jvTop();     // Get JV top member
        int jvSize();           // Get JV squad size
        bool jvEmpty();         // Is JV squad empty?
        int getTeamSize();      // Get total team size
        const string getName();
        void printV();          // Print Varsity members
        void printJV();         // Print JV members
        void printTeam();       // Print all team members
    private:
        TeamMember* S;
        int capacity; // stack capacity
        int vTopP;    // Top index for Varsity stack
        int jvTopP;   // Top index for JV stack
        int numJV;
        int numV;
        const string teamName;
};

// Constructor
Team::Team(int cap, const string name) : capacity(cap), vTopP(-1), 
                                         jvTopP(cap), numJV(0), numV(0), 
                                         S(new TeamMember[cap]), teamName(name) {}

// Destructor
Team::~Team() {
    delete[] S; 
}

// Push to varsity stack
void Team::vPush(const std::string& name) {
    if (/*vTopP + 1 == jvTopP*/(vSize() + jvSize()) == capacity) throw StackFull("Cannot add more Varsity members.");
    TeamMember* member = new TeamMember(name);
    S[++vTopP] = *member; // Use inherited array for Varsity
    numV++;
}

// Pop from varsity stack
void Team::vPop() {
    if (vEmpty()) throw StackEmpty("No Varsity members to pop.");
    vTopP--;
    numV--;
}

// Get Varsity top member
TeamMember Team::vTop() {
    return S[vTopP];
}

// Get Varsity squad size
int Team::vSize() {
    return numV;
}

// Is Varsity squad empty?
bool Team::vEmpty() {
    /*return (vSize() == 0);*/
    return (numV == 0);
}

// Push to JV stack
void Team::jvPush(const std::string& name) {
    if (/*jvTopP - 1 == vTopP*/(vSize() + jvSize()) == capacity) throw StackFull("Cannot add more JV members.");
    TeamMember* member = new TeamMember(name);
    S[--jvTopP] = *member; // Use inherited array for JV
    numJV++;
}

// Pop from JV stack
void Team::jvPop() {
    if (jvEmpty()) throw StackEmpty("No JV members to pop.");
    jvTopP++;
    numJV--;
}

// Get JV top member
TeamMember Team::jvTop() {
    return S[jvTopP];
}

// Get JV squad size
int Team::jvSize() {
    return numJV;
}

// Is JV squad empty?
bool Team::jvEmpty() {
    return (numJV == 0);
}

// Get total team size
int Team::getTeamSize() {
    return (vSize() + jvSize());
}

const string Team::getName() {
    return teamName;
}

// Print varsity team members from top to bottom
void Team::printV() {
    if (vEmpty()) cout << "No Varsity members.\n";
    else {
        cout << "Varsity members:\n";
        for (int i = vTopP; i >= 0; i--) {
            cout << S[i].getName() << "\n";
        }
    }
}

// Print JV team members from top to bottom
void Team::printJV() {
    if (jvEmpty()) cout << "No JV members.\n";
    else {
        cout << "JV members:\n";
        for (int i = jvTopP; i < capacity; i++) {
            cout << S[i].getName() << "\n";
        }
    }
}

// Print JV team members from top to bottom
void Team::printTeam() {
    cout << teamName << " team members:\n\n";
    printJV();
    cout << "\n";
    printV();
}

#endif // TEAM_HPP