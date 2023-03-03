#pragma once

#ifndef CL_SESSION_HPP_INCLUDED_
#define CL_SESSION_HPP_INCLUDED_

#include <string>
#include <vector>
#include <ctime>
#include <ostream>
#include <memory>

// Session type
// Used for session data storage and manipulation
class session_t
{
public:
    session_t(std::string const& name, std::vector<std::string> const& labels, std::string const& comment);
    session_t(session_t&& other) = default;

    session_t(session_t const&) = delete;
    session_t& operator=(session_t const&) = delete;

    // Finishes the session by setting finish time
    void finish() noexcept;

    // Checks if the session is finished
    bool not_finished() const noexcept { return m_finish_time.get() == nullptr; }

    // Resets the attributes of the session
    void reset(std::string const& name, std::vector<std::string> const& labels, std::string const& comment) noexcept;

public: // @todo safe member management
    std::string m_name;
    std::vector<std::string> m_labels;
    std::string m_comment;
    std::unique_ptr<tm> m_start_time;
    std::unique_ptr<tm> m_finish_time;
}; // class session_t

// Overloaded inserter operator for ease of use
std::ostream& operator<<(std::ostream& os, session_t const& process);

#endif // CL_SESSION_HPP_INCLUDED_