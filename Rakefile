# encoding: utf-8
#
# Copyright:: 2009-2016 Doc Walker
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

require 'git'
require 'github_changelog_generator/task'
require 'rake'
require 'rubygems'
require 'rake/version_task'         # gem install version
require 'version'

# requires additional packages on MacOS (including Homebrew):
# $ /usr/bin/ruby -e "$(curl -fsSL \
#   https://raw.githubusercontent.com/Homebrew/install/master/install)"
# $ brew install doxygen        # generates documentation from source code
# $ brew cask install mactex    # MacTeX

Rake::VersionTask.new do |task|
  # prevent auto-commit on version bump
  task.with_git = false
end

# adjust as appropriate
CWD             = File.expand_path(File.dirname(__FILE__))
DOXYFILE        = 'Doxyfile'
GITHUB_USERNAME = '4-20ma'
GITHUB_REPO     = 'ModbusMaster'
HEADER_FILE     = "#{GITHUB_REPO}.h"
CHANGELOG_FILE  = 'CHANGELOG.md'
PROPERTIES_FILE = 'library.properties'
VERSION_FILE    = Version.version_file('').basename.to_s


task :default => :info

desc 'Display instructions for public release'
task :info do
  puts <<-EOF.gsub(/^\s{2}/, '')

  Instructions for public release

  - Update version, as appropriate:

    $ rake version:bump           # or
    $ rake version:bump:minor     # or
    $ rake version:bump:major     # or
    edit 'VERSION' file directly

  - Prepare release date, 'CHANGELOG.md' file, documentation:

    $ rake prepare

  - Review changes to 'CHANGELOG.md' file
    This file is assembled using git commit messages; review for completeness.

  - Review html documentation files
    These files are assembled using source code Doxygen tags; review for
    for completeness.

  - Add & commit source files, tag, push to origin/master;
    add & commit documentation files, push to origin/gh-pages:

    $ rake release

  EOF
end # task :info


desc "Prepare #{CHANGELOG_FILE} for release"
task :prepare => 'prepare:default'

namespace :prepare do
  task :default => [
    :release_date,
    :library_properties,
    :changelog,
    :documentation
  ]

  desc 'Prepare documentation'
  task :documentation do
    version = Version.current.to_s

    # update parameters in Doxyfile
    file = File.join(CWD, 'doc', DOXYFILE)

    contents = IO.read(file)
    contents.sub!(/(^PROJECT_NUMBER\s*=)(.*)$/) do |match|
      "#{$1} v#{version}"
    end # contents.sub!(...)
    IO.write(file, contents)

    # chdir to doc/ and call doxygen to update documentation
    Dir.chdir(to = File.join(CWD, 'doc'))
    system('doxygen', DOXYFILE)

    # chdir to doc/latex and call doxygen to update documentation
    Dir.chdir(from = File.join(CWD, 'doc', 'latex'))
    system('make')

    # move/rename file to 'extras/GITHUB_REPO reference-x.y.pdf'
    to = File.join(CWD, 'extras')
    FileUtils.mv(File.join(from, 'refman.pdf'),
      File.join(to, "#{GITHUB_REPO} reference-#{version}.pdf"))
  end # task :documentation

  desc 'Prepare release history'
  GitHubChangelogGenerator::RakeTask.new(:changelog) do |config|
    config.add_issues_wo_labels = false
    config.add_pr_wo_labels = false
    config.enhancement_labels = [
      'Type: Enhancement'
    ]
    config.bug_labels = ['Type: Bug']
    config.exclude_labels = ['Type: Question']
    config.header = '# ModbusMaster CHANGELOG'
    config.include_labels = [
      'Type: Bug',
      'Type: Enhancement',
      'Type: Feature Request',
      'Type: Maintenance'
    ]
    # config.since_tag = '0.1.0'
    config.future_release = "v#{Version.current.to_s}"
    config.user = GITHUB_USERNAME
    config.project = GITHUB_REPO
  end # GitHubChangelogGenerator::RakeTask.new

  desc 'Update version in library properties file'
  task :library_properties do
    version = Version.current.to_s

    file = File.join(CWD, PROPERTIES_FILE)

    contents = IO.read(file)
    contents.sub!(/(version=\s*)(.*)$/) do |match|
      "#{$1}#{version}"
    end # contents.sub!(...)
    IO.write(file, contents)
  end # task :library_properties

  desc 'Update release date in header file'
  task :release_date do
    file = File.join(CWD, 'src', HEADER_FILE)

    contents = IO.read(file)
    contents.sub!(/(\\date\s*)(.*)$/) do |match|
      "#{$1}#{Time.now.strftime('%-d %b %Y')}"
    end # contents.sub!(...)
    IO.write(file, contents)
  end # task :release_date

end # namespace :prepare


desc 'Release source & documentation'
task :release => 'release:default'

namespace :release do
  task :default => [:source, :documentation]

  desc 'Commit documentation changes related to version bump'
  task :documentation do
    version = Version.current.to_s
    cwd = File.expand_path(File.join(File.dirname(__FILE__), 'doc', 'html'))
    g = Git.open(cwd)

    # `git add .`
    g.add

    # remove each deleted item
    g.status.deleted.each do |item|
      g.remove(item[0])
    end # g.status.deleted.each

    # commit changes if items added, changed, or deleted
    if g.status.added.size > 0 || g.status.changed.size > 0 ||
      g.status.deleted.size > 0 then
      message = "Update documentation for v#{version}"
      puts g.commit(message)
    else
      puts "No changes to commit v#{version}"
    end # if g.status.added.size > 0 || g.status.changed.size > 0...

    g.push('origin', 'gh-pages')
  end # task :documentation

  desc 'Commit source changes related to version bump'
  task :source do
    version = Version.current.to_s
    `git add \
      doc/#{DOXYFILE} \
      "extras/#{GITHUB_REPO} reference-#{version}.pdf" \
      src/#{HEADER_FILE} \
      #{CHANGELOG_FILE} \
      #{PROPERTIES_FILE} \
      #{VERSION_FILE} \
    `
    `git commit -m 'Version bump to v#{version}'`
    `git tag -a -f -m 'Version v#{version}' v#{version}`
    `git push origin master`
    `git push --tags`
  end # task :source

end # namespace :release
