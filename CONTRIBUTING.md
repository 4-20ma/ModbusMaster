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

    ```` bash
    $ make
    ````

    Project must build successfully using `make` in order for contribution to be considered.

- Make commits of logical units
    - Check for unnecessary whitespace with `git diff --check` before committing
    - Each commit should represent one atomic change and should stand on its own
    - Write a [good commit message](http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html)

- Push to your fork and [submit a pull request](https://github.com/4-20ma/ModbusMaster/compare/)
- [Code of conduct](https://github.com/4-20ma/ModbusMaster/blob/master/CODE_OF_CONDUCT.md)

### Labels

Project maintainers assign labels to Issues and Pull Requests (PRs) to categorize, prioritize, and provide status. The following guidelines and conventions are used in this project:

#### Type

- `Bug` - existing code does not behave as described in the project documentation; _requires_ clear test case and be _reproducible_ by project maintainer
- `Enhancement` - improvement to an existing feature (Issue or Pull Request)
- `Feature Requst` - new functionality; _requires_ a well-written, clear user story (Issue)
- `Maintenance` - minor administrative change that does not provide enhancement or introduce new feature
- `Question` - self-explanatory

#### Priority

- `Low` - default priority; new issues generally start here
- `Medium` - issues are escalated, depending on severity of the issue
- `High` - issues are escalated, depending on severity of the issue
- `Critical` - these issues are to be resolved ahead of any other

#### Status

- `Abandoned` - issue/PR closed due to inactivity
- `Blocked` - issue/PR will not be resolved/merged (some projects label these items as `wontfix`; include explanation in issue/PR)
- `In Progress` - issue has been assigned and is actively being addressed; re-label issue `On Hold` with explanation if there will be a significant delay
- `Maintainer Review Needed` - last step prior to merge; PR passes continuous integration tests and is able to be cleanly merged - awaiting review for style, code cleanliness, etc.
- `On Hold` - implementation delayed; provide explanation in issue/PR
- `Pending Contributor Response` - issue/PR closed after 14 days of inactivity (re-label `Abandoned` at closure)
