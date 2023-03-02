#pragma once
#ifndef CL_SESSION_MANAGER_HPP_INCLUDED_
#define CL_SESSION_MANAGER_HPP_INCLUDED_

#include <string>
#include <vector>
#include <fstream>

#include "cl_session.hpp"

// Session manager type, singleton class
// Used for managing sessions and the file structure of the application, interfaces with the user via the console
class session_manager_t
{
public:
    session_manager_t(std::string const& path);

    ~session_manager_t();

    session_manager_t(session_manager_t const&) = delete;
    session_manager_t& operator=(session_manager_t const&) = delete;

    // Starts a new session
    void start_new_session(std::string const& session_name, std::vector<std::string> const& session_labels, std::string const& session_comment) noexcept;

    // Returns the last (currently active) session
    session_t& get_last_session() noexcept;

private:
    std::fstream m_file;
    std::vector<session_t> m_sessions;
}; // class session_manager_t;

#endif // CL_SESSION_MANAGER_HPP_INCLUDED_