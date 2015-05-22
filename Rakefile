# encoding: utf-8

require 'git'
require 'rake'
require 'rubygems'
require 'rake/version_task'         # gem install version
require 'version'

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
HISTORY_FILE    = 'HISTORY.md'
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
    
  - Prepare release date, 'HISTORY.md' file, documentation:
  
    $ rake prepare
    
  - Review changes to 'HISTORY.md' file
    This file is assembled using git commit messages; review for completeness.
  
  - Review html documentation files
    These files are assembled using source code Doxygen tags; review for
    for completeness.
  
  - Add & commit source files, tag, push to origin/master;
    add & commit documentation files, push to origin/gh-pages:
  
    $ rake release
    
  EOF
end # task :info


desc 'Prepare HISTORY file for release'
task :prepare => 'prepare:default'

namespace :prepare do
  task :default => [
    :release_date,
    :library_properties,
    :history,
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
    
    # move/rename file to 'doc/GITHUB_REPO reference-x.y.pdf'
    FileUtils.mv(File.join(from, 'refman.pdf'),
      File.join(to, "#{GITHUB_REPO} reference-#{version}.pdf"))
  end # task :documentation
  
  desc 'Prepare release history'
  task :history, :tag do |t, args|
    g = Git.open(CWD)
    
    current_tag = args[:tag] || Version.current.to_s
    prior_tag = g.tags.last
    
    history = "## [v#{current_tag} (#{Time.now.strftime('%Y-%m-%d')})]"
    history << "(/#{GITHUB_USERNAME}/#{GITHUB_REPO}/tree/v#{current_tag})\n"
    
    commits = prior_tag ? g.log.between(prior_tag) : g.log
    history << commits.map do |commit|
      "- #{commit.message}"
    end.join("\n")
    history << "\n\n---\n"
    
    file = File.join(CWD, HISTORY_FILE)
    puts "Updating file #{file}:"
    puts history
    contents = IO.read(file)
    IO.write(file, history << contents)
  end # task :history
  
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
    file = File.join(CWD, HEADER_FILE)
    
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
    `git add doc/#{DOXYFILE} "doc/#{GITHUB_REPO} reference-#{version}.pdf" \
      #{HEADER_FILE} #{HISTORY_FILE} #{PROPERTIES_FILE} #{VERSION_FILE}`
    `git commit -m 'Version bump to v#{version}'`
    `git tag -a -f -m 'Version v#{version}' v#{version}`
    `git push origin master`
    `git push --tags`
  end # task :source
  
end # namespace :release
