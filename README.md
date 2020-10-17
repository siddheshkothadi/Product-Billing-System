# Product-Billing-System
PBL project

## Clone

<b>Note:</b> For this you need to install git on your machine. You can download the git tool from <a href="https://git-scm.com/">here</a>.

- First, fork this repository.
- Run the following command in command prompt to clone your forked repo locally :

  ```bash
    git clone https://github.com/YOUR_GITHUB_USER_NAME/Product-Billing-System
  ```
  where <code>YOUR_GITHUB_USER_NAME</code> is your GitHub username.

## Setting up upstream

- When a repository is cloned, it has a default remote named origin that points to your fork on GitHub, not the original repository it was forked from. To keep track of the original repository, you should add another remote named upstream. For this project it can be done by running the following command 

  ```bash
    git remote add upstream https://github.com/siddheshkothadi/Product-Billing-System
  ```

- Now to test the upstream, run the following command, you'll see an output similar to the output below
  ```bash
    git remote -v
    origin  https://github.com/YOUR_GITHUB_USER_NAME/Product-Billing-System(fetch)
    origin  https://github.com/YOUR_GITHUB_USER_NAME/Product-Billing-System (push)
    upstream        https://github.com/siddheshkothadi/Product-Billing-System.git (fetch)
    upstream        https://github.com/siddheshkothadi/Product-Billing-System.git (push)
  ```
  
- To fetch latest changes from the upstream, run the following command: 
    ```bash
      git fetch upstream
    ```
    
- To merge these changes, run the following command : 
  ```bash
    git merge upstream/develop
  ```

## Sending a Pull Request

- Commit some changes on your forked repository.

- Then, you'll see an option to send a pull request on the top right corner of your forked repository, click on it and create a pull request.
