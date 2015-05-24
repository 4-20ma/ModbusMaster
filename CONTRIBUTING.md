Contributing
============

- Fork, then clone the repo:
    ````
    git clone git@github.com:your_username/ModbusMaster.git
    ````

- Create a topic branch from where you want to base your work
    - This is usually the master branch
    - Only target release branches if you are certain your fix must be on that branch
    - To quickly create a topic branch based on master; `git checkout -b fix/master/my_contribution master`. Please avoid working directly on the `master` branch.

- Follow the [style guide](https://github.com/4-20ma/ModbusMaster/blob/master/STYLE.md)

- Test your change

- Make commits of logical units
    - Check for unnecessary whitespace with `git diff --check` before committing
    - Each commit should represent one atomic change and should stand on its own
    - Write a [good commit message](http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html)

- Push to your fork and [submit a pull request](https://github.com/4-20ma/ModbusMaster/compare/)
