#include <iostream>

#include "cl_session_manager.hpp"
#include "cl_parse.hpp"

session_manager_t::session_manager_t(std::string const& path)
: m_file{path}
{
    // check if file exists
    if (!m_file.good())
    {
        // if not, create and print header
        m_file.open(path, std::ios::out);
        csv_parse::print_session_header(m_file);
    }
    else
    {
        // if so, reopen in append mode
        m_file.close();
        m_file.open(path, std::ios::app);
    }
    // default unnamed session (gets reset in main)
    start_new_session("Unnamed session", {""}, "");
}

session_manager_t::~session_manager_t()
{
    if(m_sessions.rbegin()->not_finished())
        m_sessions.rbegin()->finish();
    m_file << *m_sessions.rbegin();
    m_file.close();
}

void session_manager_t::start_new_session(
    std::string const& session_name,
    std::vector<std::string> const& session_labels,
    std::string const& session_comment) noexcept
{
    // Write old session to the file
    if (!m_sessions.empty()) {
        m_sessions.rbegin()->finish();
        m_file << *m_sessions.rbegin();
    }
    // Construct new session
    m_sessions.emplace_back(session_name, session_labels, session_comment);
}

session_t& session_manager_t::get_last_session() noexcept
{
    return *m_sessions.rbegin();
}