# Unmellow Yellow Autonomous Snowplow Robot

## Description
The **Unmellow Yellow Autonomous Snowplow Robot** is designed to autonomously clear snow in a designated area, avoiding obstacles like boxes and other robots. The robot uses **skid steering** with 4 motors, enabling it to navigate around obstacles and follow a predetermined path marked by a black perimeter. Equipped with multiple sensors, including IR, ultrasonic, and IMU, the robot detects its surroundings and makes real-time decisions to clear the area efficiently.

The goal of this project is to automate snow clearing, offering a solution that reduces manual labor and enhances efficiency, safety, and productivity for property owners and municipalities.

## Table of Contents
- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)
- [Authors](#authors)

## Installation
To install and run this project, follow the steps below:

1. **Clone the Repository**:
   Clone the repository to your local machine:
   ```bash
   git clone https://github.com/UnmellowYellow/autonomous-snowplow-robot.git


## Appendix

This file contains all of the commands required in order to run the code for our project. The main purpose behind this project is to create an Autonomous Snowplow robot.
Below are a series of useful Github commands to perform various operations on a repository. Before performing the commands, make sure to complete everything in Phase 0 (cloning the repo and having access to it):

PHASE 0: Accessing The Repository
MANDATORY:

git clone <repository-url>
cd repository

OPTIONAL:
git remote -v //Automatically setting up a remote
git remote add origin <repository-url> //Manually if needed
git checkout -b <new-branch-name> //Creating a new branch

PHASE 1: Basic Git Commands

git init //Creates a Git repository and allows local access
git status 
git add <file>
git add .  //To add all modified files
git commit -m "Your commit message"
git log
git diff
git diff --staged
git restore <file>

PHASE 2: BRANCHING AND MERGING

git branch <branch-name>
git checkout <branch-name>
git checkout -b <branch-name>
git branch -d <branch-name> //Delete a branch locally
git push origin --delete <branch-name> //Delete a remote branch
git push --all //Push all branches to a remote repository

PHASE 3: ADDING FILES & COMMITTING TO THE REPO

git add <file> //Adding files
git commit -m "Your commit message" //Committing changes
git commit -am "Your commit message" //Adding files & committing changes at the same time
git commit -m "Add new directory" //Adding a new directory
git push origin main //Pushing individual changes to the remote repository

PHASE 4: CREATING FILES IN THE DIRECTORY

touch <directory-name>/<file-name> //Creating a file
git add <directory-name>/<file-name> //Adding a file to git
git commit -m "Add <file-name> to <directory-name>" //Committing changes
git push origin main //Pushing changes to the remote repository 
