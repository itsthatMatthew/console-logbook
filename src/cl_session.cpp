#include "cl_session.hpp"
#include "cl_parse.hpp"

session_t::session_t(
    std::string const& name,
    std::vector<std::string> const& labels,
    std::string const& comment
)
: m_name{name},
  m_labels{labels},
  m_comment{comment},
  m_start_time{nullptr},
  m_finish_time{nullptr}
{
    time_t current_time = std::time(0);
    m_start_time.reset(new tm{*std::localtime(&current_time)});
}

void session_t::finish() noexcept
{
    time_t current_time = std::time(0);
    m_finish_time.reset(new tm{*std::localtime(&current_time)});
}

void session_t::reset(
    std::string const& name,
    std::vector<std::string> const& labels,
    std::string const& comment
) noexcept
{
    // Overwrite members except time values
    m_name = name;
    m_labels = labels;
    m_comment = comment;
}

std::ostream& operator<<(std::ostream& os, session_t const& session)
{
    return csv_parse::print_filtered_session<false>(os, session);
}