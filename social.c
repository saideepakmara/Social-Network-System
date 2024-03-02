#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "social.h" 

// Global variables for storing nodes and a counter
Node* set_of_nodes = NULL;
int counter = 0;

// Function to add a birthday to an individual node
void addBirthday(Node* node, char* birthday) {
    printf("Would you like to add a birthday? (Y/N): ");
    char reply[2];
    scanf("%s", reply);
    if (strcmp(reply, "Y") == 0) {
        printf("Enter the birthday (DD-MM-YYYY): ");
        scanf("%s", node->birthday);
    } else {
        node->birthday[0] = '\0';
    }
}

// Function to add owners to a business node
void addOwners(Node* business, Node* individual) {
    char reply[2];
    printf("\nWant to add owners? (Y/N): ");
    scanf("%s", reply);
    while (strcmp(reply, "N") != 0 && business->ownerIndex < MAX_LINKS) {
        printf("Enter owner's ID: ");
        int ownerID;
        scanf("%d", &ownerID);
        Node* owner = search_ID(ownerID);
        if (owner != NULL && strcmp(owner->type, "Individual") == 0) {
            business->owners[business->ownerIndex] = owner;
            business->ownerIndex++;

            owner->ownerOf[owner->ownerOfIndex] = business;
            owner->ownerOfIndex++;
            printf("%s is now an owner of %s.\n", owner->name, business->name);
        } else {
            printf("%s is NOT APPLICABLE\n", owner->name);
        }
        printf("Want to add more owners? (Y/N): ");
        scanf("%s", reply);
    }
}

// Function to add customers to a business node
void addCustomers(Node* business, Node* individual) {
    char reply[2];
    printf("\nWant to add customers? (Y/N): ");
    scanf("%s", reply);
    while (strcmp(reply, "N") != 0 && business->customerIndex < MAX_LINKS) {
        printf("Enter customer's ID: ");
        int customerID;
        scanf("%d", &customerID);
        Node* customer = search_ID(customerID);
        if (customer != NULL && strcmp(customer->type, "Individual") == 0) {
            business->customers[business->customerIndex] = customer;
            business->customerIndex++;

            customer->customerOf[customer->customerOfIndex] = business;
            customer->customerOfIndex++;
            printf("%s is now a customer of %s.\n", customer->name, business->name);
        } else {
            printf("%s is NOT APPLICABLE\n", customer->name);
        }
        printf("Want to add more customers? (Y/N): ");
        scanf("%s", reply);
    }
}

// Function to add group members to a group node
void addGroupMembers(Node* group) {
    char reply[2];
    printf("\nWant to add members? (Y/N): ");
    scanf("%s", reply);
    while (strcmp(reply, "N") != 0 && group->memberIndex < MAX_LINKS) {
        printf("Enter member's ID: ");
        int memberID;
        scanf("%d", &memberID);
        Node* member = search_ID(memberID);
        if (member != NULL) {
            group->members[group->memberIndex] = member;
            group->memberIndex++;

            member->memberOf[member->memberOfIndex] = group;
            member->memberOfIndex++;
            printf("%s is now a member of %s.\n", member->name, group->name);
        } else {
            printf("%s is NOT APPLICABLE\n", member->name);
        }
        printf("Want to add more members? (Y/N): ");
        scanf("%s", reply);
    }
}

// Function to add organization members to an organization node
void addOrganisationMembers(Node* organisation) {
    char reply[2];
    printf("\nWant to add members? (Y/N): ");
    scanf("%s", reply);
    while (strcmp(reply, "N") != 0 && organisation->memberIndex < MAX_LINKS) {
        printf("Enter member's ID: ");
        int memberID;
        scanf("%d", &memberID);
        Node* member = search_ID(memberID);
        if (member != NULL) {
            organisation->members[organisation->memberIndex] = member;
            organisation->memberIndex++;

            member->memberOf[member->memberOfIndex] = organisation;
            member->memberOfIndex++;
            printf("%s is now a member of %s.\n", member->name, organisation->name);
        } else {
            printf("%s is NOT APPLICABLE\n", member->name);
        }
        printf("Want to add more members? (Y/N): ");
        scanf("%s", reply);
    }
}

// Function to create a new node
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    counter++;
    newNode->set_of_postedContent = NULL;
    newNode->next = NULL;

    // Set all index values to 0
    newNode->ownerOfIndex = 0;
    newNode->customerOfIndex = 0;
    newNode->memberOfIndex = 0;
    newNode->ownerIndex = 0;
    newNode->customerIndex = 0;
    newNode->memberIndex = 0;

    printf("\nEnter the name: ");
    scanf("%s", newNode->name);

    printf("\nEnter the ID: ");
    scanf("%d", &newNode->id);

    printf("Enter the Creation Date (DD-MM-YYYY): ");
    scanf("%s", newNode->creation_date);

    printf("NODE CREATION\n");
    printf("Select the type of node :\n");
    printf("1. Individual\n2. Business\n3. Group\n4. Organisation\n");
    printf("Your choice: ");
    int type;
    scanf("%d", &type);

    // Based on the selected type, set node properties
    switch (type) {
        case 1:
            strcpy(newNode->type, "Individual");
            addBirthday(newNode, newNode->birthday);
            break;
        case 2:
            strcpy(newNode->type, "Business");
            printf("Enter the location (x & y): "); 
            scanf("%lf%lf", &newNode->x,&newNode->y);
            addOwners(newNode, newNode);
            addCustomers(newNode, newNode);
            break;
        case 3:
            strcpy(newNode->type, "Group");
            addGroupMembers(newNode);
            break;
        case 4:
            strcpy(newNode->type, "Organisation");
            addOrganisationMembers(newNode);
            break;
        default:
            printf("Invalid Response\n");
            free(newNode);
            return NULL;
    }

    return newNode;
}

// Function to search for a node based on ID
Node* search_ID(int ID) {
    Node* current = set_of_nodes;
    while (current != NULL) {
        if (current->id == ID) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to delete a node
void deleteNode() {
    printf("\n---- NODE DELETION ----\n");

    printf("Enter the node ID to be deleted: ");
    int ID;
    scanf("%d", &ID);

    Node* current = set_of_nodes;
    Node* previous = NULL;
    // Traverse the linked list to find node with required ID
    while (current != NULL) {
        if (current->id == ID) {
            if (previous == NULL) {
                // If the node to be deleted is first node
                set_of_nodes = current->next;  // Update the head of the linked list
            } else {
                // If the node to be deleted isn't first node
                previous->next = current->next; // Update the previous node's next pointer
            }

            free(current);
            printf("DELETION SUCCESSFUL\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("DELETION UNSUCCESSFUL\n");
}

// Helper function to search for nodes based on specified attributes
Node* searchNode(char attribute, char* value) {
    Node* current = set_of_nodes;
    Node* searchResults = NULL;
    Node* lastResult = NULL;

    // Traverse the linked list to find nodes with matching attributes
    while (current != NULL) {
        if ((attribute == '1' && strcmp(current->name, value) == 0) ||
            (attribute == '2' && strcmp(current->type, value) == 0) ||
            (attribute == '3' && strcmp(current->birthday, value) == 0)) {
            Node* resultNode = (Node*)malloc(sizeof(Node));
            resultNode->id = current->id;
            strcpy(resultNode->name, current->name);
            strcpy(resultNode->type, current->type);
            strcpy(resultNode->birthday, current->birthday);
            resultNode->next = NULL;

            if (searchResults == NULL) {
                searchResults = resultNode;
                lastResult = resultNode;
            } else {
                lastResult->next = resultNode;
                lastResult = resultNode;
            }
        }
        current = current->next;
    }
    return searchResults;
}

// Function to search for nodes
void search(){
    printf("\n---- NODE SEARCH ----\n");
            printf("Select the attribute by which you want to search:\n");
            printf("1. Name\n2. Type\n3. Birthday\n");
            printf("Your response: ");
            char attribute[2];
            scanf("%s", attribute);
            char value[100];
            if (attribute[0] == '1' || attribute[0] == '2' || attribute[0] == '3') {
                printf("Enter the value: ");
                scanf("%s", value);
                Node* searchResults = searchNode(attribute[0], value);
                printf("Searching...\n");
                if (searchResults != NULL) {
                    printf("SEARCH RESULT:\n");
                    while (searchResults != NULL) {
                        printbasedata(searchResults);
                        Node* temp = searchResults;
                        searchResults = searchResults->next;
                        free(temp);
                    }
                } else {
                    printf("\nNO RESULTS FOUND\n");
                }
            } else {
                printf("\nInvalid response\n");
            }
}

// Function to print basic data of a node
void printbasedata(Node* node) {
    printf("---------------------------------------------------\n");
    printf("User ID: %d\n", node->id);
    printf("Name: %s\n", node->name);
    printf("User Type: %s\n", node->type);
    printf("---------------------------------------------------\n");
}

// Function to print 1-hop linked nodes of a given node
void print1hop() {

    printf("Enter the user ID: ");
    int ID;
    scanf("%d", &ID);
    Node* node = search_ID(ID);
            
    if (node != NULL) {

      printf("\n---- 1-HOP LINKED NODES ----\n");
      printf("---------------------------------------------------\n");
      printf("User ID: %d\n", node->id);
      printf("Name: %s\n", node->name);
      printf("User Type: %s\n", node->type);

      // Check the type of the node and print linked nodes accordingly
      if (strcmp(node->type, "Business") == 0) {
          printf("Linked Owners: ");
          for (int i = 0; i < node->ownerIndex; i++) {
              printf("%s (ID: %d), ", node->owners[i]->name, node->owners[i]->id);
          }
          printf("\n");

          printf("Linked Customers: ");
          for (int i = 0; i < node->customerIndex; i++) {
            printf("%s (ID: %d), ", node->customers[i]->name, node->customers[i]->id);
          }
          printf("\n");

          printf("Linked Groups: ");
          for (int i = 0; i < node->memberOfIndex; i++) {
              printf("%s (ID: %d), ", node->memberOf[i]->name, node->memberOf[i]->id);
          }
          printf("\n");

      } else if (strcmp(node->type, "Individual") == 0) {
          printf("Linked Business(Owner OF): ");
          for (int i = 0; i < node->ownerOfIndex; i++) {
              printf("%s (ID: %d), ", node->ownerOf[i]->name, node->ownerOf[i]->id);
          }
          printf("\n");
  
          printf("Linked Business(Customer OF): ");
          for (int i = 0; i < node->customerOfIndex; i++) {
              printf("%s (ID: %d), ", node->customerOf[i]->name, node->customerOf[i]->id);
          }
          printf("\n");
 
          printf("Linked Group/Organisation(Member OF): ");
          for (int i = 0; i < node->memberOfIndex; i++) {
              printf("%s (ID: %d), ", node->memberOf[i]->name, node->memberOf[i]->id);
          }
          printf("\n");
      } else if (strcmp(node->type, "Group") == 0 || strcmp(node->type, "Organisation") == 0) {
          printf("Linked Members: ");
          for (int i = 0; i < node->memberIndex; i++) {
              printf("%s (ID: %d), ", node->members[i]->name, node->members[i]->id);
          }
          printf("\n");
      }

      printf("---------------------------------------------------\n");
    }
    else {
        printf("\nUSER NOT FOUND\n");
    }
}

// Function to create and post content by a user
void createAndPostContent(Node* nodes) {
    printf("\n---- CREATE AND POST CONTENT ----\n");
    printf("Enter the user ID: ");
    int id;
    scanf("%d", &id);
    getchar(); // TO consume newline character 

    Node* userNode = search_ID(id);
    if (userNode != NULL) {
        char reply[2] = "Y";
        while (strcmp(reply, "N\n") != 0) {
            printf("Enter the content: ");
            char content[100];
            scanf(" %[^\n]", content);
            getchar(); // To consume newline character

            if (userNode->set_of_postedContent == NULL) {
                userNode->set_of_postedContent = (Node*)malloc(sizeof(Node));
                userNode->set_of_postedContent->next = NULL;
                strcpy(userNode->set_of_postedContent->name, content);
            } else {
                 // Allocate memory for a new content node and link it to the existing content nodes
                Node* contentNode = (Node*)malloc(sizeof(Node));
                contentNode->next = userNode->set_of_postedContent;
                strcpy(contentNode->name, content);
                userNode->set_of_postedContent = contentNode;
            }

            printf("Are you sure you want to post? (Y/N): ");
            scanf("%s", reply);

            if (strcmp(reply, "Y") == 0) {
                printf("\n++ Content Posted ++\n");
            } else {
                printf("\n-- Content not Posted --\n");
                break;
            }

            if (strcmp(reply, "N") != 0) {
                printf("Want to create any more content? (Y/N): ");
                scanf("%s", reply);
                if (strcmp(reply, "Y") != 0) break;
            }
        }
    } else {
        printf("\nUSER NOT FOUND\n");
    }
}

// Function to search for content posted by any user/node
void searchForContent(Node* nodes) {
    printf("\n---- SEARCH FOR CONTENT ----\n");
    getchar(); // TO consume newline character 
    printf("Enter the content to search: ");
    char content[100];
    scanf("%[^\n]", content);
    

    int found = 0;

    Node* currentNode = nodes;
    while (currentNode != NULL) {
        Node* contentNode = currentNode->set_of_postedContent;
        while (contentNode != NULL) {
            if (strcmp(contentNode->name, content) == 0) {
                found = 1;
                printf("Content '%s' posted by user '%s' (ID: %d)\n", content, currentNode->name, currentNode->id);
            }
            contentNode = contentNode->next;
        }
        currentNode = currentNode->next;
    }

    if (!found) {
        printf("Content '%s' not found.\n", content);
    }
}

// Function to display content linked to an individual node
void displayContentLinkedToIndividual() {

    printf("Enter the ID of the individual: ");
    int individualID;
    scanf("%d", &individualID);

    Node* individual = search_ID(individualID);

    if (individual != NULL && strcmp(individual->type, "Individual") == 0) {
        printf("\n---- DISPLAY CONTENT LINKED TO INDIVIDUAL '%s' (ID: %d) ----\n", individual->name, individual->id);

    // Iterate through each group or organization linked to the individual
    for (int i = 0; i < individual->memberOfIndex; i++) {
        Node* groupOrOrganization = individual->memberOf[i];

        printf("Content posted by members of '%s' (ID: %d):\n", groupOrOrganization->name, groupOrOrganization->id);

        // Iterate through each member of the group or organization
        for (int j = 0; j < groupOrOrganization->memberIndex; j++) {
            Node* member = groupOrOrganization->members[j];

            // Check if the member is an individual
            if (strcmp(member->type, "Individual") == 0) {
                printf("Content posted by '%s' (ID: %d):\n", member->name, member->id);

                // Traverse through the posted content of the individual
                Node* contentNode = member->set_of_postedContent;
                while (contentNode != NULL) {
                    printf("- %s\n", contentNode->name);
                    contentNode = contentNode->next;
                }
            }
        }
    }
    } else {
        printf("\nINVALID INDIVIDUAL ID OR NOT AN INDIVIDUAL\n");
    }

}

// Function to print all nodes and their information in the social network
void printAllNodesInSystem(Node* nodes) {
    printf("\n---- PRINTING ALL NODES IN THE SYSTEM ----\n");
    Node* currentNode = nodes;

    while (currentNode != NULL) {
        
        printf("\n---------------------------\n");
        printf("User ID: %d\n", currentNode->id);
        printf("Name: %s\n", currentNode->name);
        printf("User Type: %s\n", currentNode->type);

        if (strcmp(currentNode->type, "Individual") == 0) {
            printf("Birthday: %s\n", currentNode->birthday);
        }

        if (strcmp(currentNode->type, "Business") == 0) {
            printf("Location: (%lf, %lf)\n", currentNode->x, currentNode->y);     
        }

        if (currentNode->set_of_postedContent != NULL) {
            printf("Content:\n");
            Node* contentNode = currentNode->set_of_postedContent;
            while (contentNode != NULL) {
                printf("- %s\n", contentNode->name);
                contentNode = contentNode->next;
            }
        }
        printf("\n---------------------------\n");
        printf("\n");

        currentNode = currentNode->next;
    }
}

// Function to display the menu/index of actions
void menu() {
    printf("\n--------- MENU/INDEX ----------\n");
    printf("1. Create a new node\n2. Delete an existing node\n3. Search for an existing node(Name, Type, Birthday)\n4. Print all 1-hop linked nodes\n");
    printf("5. Create and Post content for a node\n6. Search for content posted by any node\n7. Display all content posted by individuals linked to a given individual(via group/organisation)\n8. Display all nodes in the system\n9. EXIT THE NETWORK\n");
    printf("Your choice: ");
}

// Main function
int main() {
    printf("+------------THE SOCIAL NETWORK------------+\n");

    char response[2];
    menu();
    scanf("%s", response);

    // Main loop: Continues running till user chooses to exit
    while (strcmp(response, "9") != 0) {
        if (strcmp(response, "1") == 0) {
            // Option 1: Create a new node
            Node* newNode = createNode();
            if (newNode != NULL) {
                newNode->next = set_of_nodes;
                set_of_nodes = newNode;
                printf("\nCREATION SUCCESSFUL\n");
            } else {
                printf("CREATION UNSUCCESSFUL\n");
            }
        } else if (strcmp(response, "2") == 0) {
            // Option 2: Delete an existing node
            deleteNode();
        } else if (strcmp(response, "3") == 0) {
            // Option 3: Search for an existing node
            search();
        } else if (strcmp(response, "4") == 0) {
            // Option 4: Print all 1-hop linked nodes to a given input node
            print1hop();
        } else if (strcmp(response, "5") == 0) {
            // Option 5: Create and Post content by a node
            createAndPostContent(set_of_nodes);
        } else if (strcmp(response, "6") == 0) {
            // Option 6: Search for content posted by any node
            searchForContent(set_of_nodes);
        } else if (strcmp(response, "7") == 0) {
            // Option 7: Display all content posted by individuals linked to a given individual
            displayContentLinkedToIndividual();
        } else if (strcmp(response,"8")==0) {
            // Option 8: Display all nodes in the system
            printAllNodesInSystem(set_of_nodes);
        }

        menu();
        scanf("%s", response);
    }

    printf("\nEXITING NETWORK.....\n");
    return 0;
}
