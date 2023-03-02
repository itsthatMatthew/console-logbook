// Console Logbook - lightweight progress logger
// v0.1.12 alpha-build: incomplete codebase
// Copyright (c) Máté Csizmadia

#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>

#include "cl_session.hpp"
#include "cl_parse.hpp"
#include "cl_session_manager.hpp"

int main()
{
    // stores the current command given by the user in the console
    std::string current_command{};
    // session manager that handles all sessions
    session_manager_t manager{"log.csv"};

    // stores the list of commands available to process
    std::unordered_map<
        std::string,          // Name
    std::tuple<
        std::string,          // Desc
        std::function<void()> // Func
    >
    > available_commands {};
    
    { // self contained scope to fill available commands
    // commands are inserted in reverse order of display

    #define CLCMD_LAMBDA(DEF_) [&] () -> void {DEF_}

    available_commands["exit"] = {"Exit the app (ends the current session).",
    CLCMD_LAMBDA(
        std::cout << "Good bye!";
        // handled by main
    )};

    available_commands["help"] = {"List all the available commands with their description.",
    CLCMD_LAMBDA(
        std::cout << "list of available commands:" << std::endl;
        for (auto const& iter : available_commands)
        {
            std::cout << "  " << iter.first << "\t: " << std::get<0>(iter.second) << std::endl;
        }
    )};
/*
    available_commands["cfg"] = {"Edit configuration settings.",
    CLCMD_LAMBDA(
        return;
    )};
*/
    available_commands["reset"] = {"Respecify all current session settings.",
    CLCMD_LAMBDA(
        std::string name_buffer{};
        std::string labels_buffer{};
        std::vector<std::string> labels_res{};
        std::string comment_buffer{};

        std::cout << "Name of current session: ";
        std::getline(std::cin, name_buffer);
        std::cout << "Labels for current session: ";
        std::getline(std::cin, labels_buffer);
        std::stringstream labels_stream{labels_buffer};
        while(std::getline(labels_stream, labels_buffer, csv_parse::csv_delimiter))
        {
            labels_res.push_back(labels_buffer);
        }
        std::cout << "Additional comment for current session: ";
        std::getline(std::cin, comment_buffer);

        manager.get_last_session().reset(name_buffer, labels_res, comment_buffer);

        std::cout << "Current session reset:\n  ";
        csv_parse::print_filtered_session(std::cout, manager.get_last_session()) << std::endl;
    )};
/*
    available_commands["edit"] = {"Edit current session settings.",
    CLCMD_LAMBDA(
        return;
    )};
*/
    available_commands["new"] = {"Start new session with specified attributes.",
    CLCMD_LAMBDA(
        std::string name_buffer{};
        std::string labels_buffer{};
        std::vector<std::string> labels_res{};
        std::string comment_buffer{};

        std::cout << "Name of new session: ";
        std::getline(std::cin, name_buffer);
        std::cout << "Labels for new session: ";
        std::getline(std::cin, labels_buffer);
        std::stringstream labels_stream{labels_buffer};
        while(std::getline(labels_stream, labels_buffer, csv_parse::csv_delimiter))
        {
            labels_res.push_back(labels_buffer);
        }
        std::cout << "Additional comment for new session: ";
        std::getline(std::cin, comment_buffer);

        manager.start_new_session(name_buffer, labels_res, comment_buffer);

        std::cout << "New session started:\n  ";
        csv_parse::print_filtered_session(std::cout, manager.get_last_session()) << std::endl;
    )};

    available_commands["show"] = {"Shows the attributes of the current session.",
    CLCMD_LAMBDA(
        std::cout << "Current session:\n  ";
        csv_parse::print_filtered_session(std::cout, manager.get_last_session());
    )};

    #undef CLCMD_LAMBDA

    } // end of available commands fill

    std::cout << "Cosnole Logbook\nType \"help\" for list of commands." << std::endl;
    std::cout << "Please specify the attributes of the current session below..." << std::endl;
    std::get<std::function<void()>>(available_commands["reset"])();

    do
    {
        std::cin >> current_command;
        std::cin.ignore(1, '\n');

        if (available_commands.find(current_command) != available_commands.end())
        {
            std::get<std::function<void()>>(available_commands[current_command])();
        }
        else
        {
            std::cout << "Not a know command!" << std::endl;
        }
    }
    while(current_command != "exit");

    return 0;
}