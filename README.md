# Console Logbook

Passion project light-weight console application for logging work hours. 

## About the application

The app is intended to make it easier to track progress and workhours spent on specific parts of projects.

The app handles a list of sessions that have starting and finishing times.
Starting the application always starts a new session, closing it finishes the current one.
The user has the ability to start a new session during runtime, as well as rename and add multiple labels or comments to the current session.

## User interface

- show : shows the info of the current session
- new : start new session with specified attributes
  - name
  - labels
  - comment
- edit : edit session settings - **NOT IMPLEMENTED**
  - name
  - labels
  - comment
- reset : respecify all session settings
- config : edit configuration settings - **NOT IMPLEMENTED**
  - delimiter : csv delimiter format (,/;)
  - format : time format (YYYY-MM-DD HH:mm:ss)
  - output : the output file
- help : list all the available commands and what they do
- exit : exit the app with ending the current session

## To be implemented:

### One-by-one session attribute edit

#### Implementation:
The ability to edit only specific attributes of the current session.

### Config file

#### Implementation:
A cl.cfg file in the same directory as the main application, containing necessary configurational information.

#### Description:
The config file allows the user to define specific behaviours and default values of the app such as:
- the csv delimiter (comma or colon),
- the default time format,
- and the default save-path for new tasks.
