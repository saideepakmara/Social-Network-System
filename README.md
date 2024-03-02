# Social Network System in C
This repository contains the implementation of a simple social network system using C. The system models a network with different types of nodes including individuals, groups, businesses, and organizations, each with unique functionalities and relationships.

## Features

* Creation and deletion of nodes (Individual, Group, Business, Organization).
* Search functionality for nodes by name, type, or birthday.
* Listing of 1-hop linked nodes for any given node.
* Ability for nodes to create and post content.
* Search functionality for content posted by any node.
* Display of all content posted by individuals linked to a given individual through common groups or organizations.
* A master text-based interface to interact with the system, showcasing all functionalities.

## Structure

The codebase is structured into two main files:

### social.h:

This header file contains all the structure definitions and prototypes of the functions used in the program. Each structure and function is documented to explain its purpose and how it contributes to the system's functionality.
### social.c:

This file contains the implementation of all functions declared in social.h, along with any global variables used within the program.

## Key Components

* **Node**: A structure representing an entity in the network (individual, group, business, organization) with common attributes like ID, name, creation date, and posted content.
* **Individual**: A node with an optional birthday attribute.
* **Group/Organization**: Nodes that can have individuals as members.
* **Business**: A node with location attributes, capable of having individuals as owners or customers, and can be a member of groups.
