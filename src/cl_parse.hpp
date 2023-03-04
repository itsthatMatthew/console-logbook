#pragma once
#ifndef CL_PARSE_HPP_INCLUDED_
#define CL_PARSE_HPP_INCLUDED_

#include <array>
#include <string>
#include <ostream>
#include <iomanip>

#include "cl_session.hpp"

// Interface for csv parsing
namespace csv_parse
{
    constexpr std::array<char, 2> bad_csv_chars{'\"', '\n'};
    constexpr char csv_delimiter{','};
    
    // Returns the array of "illegal" CSV characters
    constexpr std::array<char, 3> get_bad_chars() noexcept
    {
        return { bad_csv_chars[0], bad_csv_chars[1], csv_delimiter };
    }

    // Prints the given text to the specified ostream in a csv compatible format
    // @param os the ostream the text should be printed at
    // @param text the text to be filtered
    // @return the ostream reference it was given
    template<bool ForceQuot = false>
    inline std::ostream& print_filtered_text(std::ostream& os, std::string const& text) noexcept;

    template<>
    inline std::ostream& print_filtered_text<true>(std::ostream& os, std::string const& text) noexcept;
    
    // Prints the session to the specified ostream in a csv compatible format
    // @param os the ostream the session should be printed at
    // @param session the session that should be printed
    // @return the ostream reference it was given
    template<bool ForceQuot = false>
    inline std::ostream& print_filtered_session(std::ostream& os, session_t const& session) noexcept;

    // Prints the session csv header to the specified ostream
    // @return the ostream reference it was given
    template<bool ForceQuot = false>
    inline std::ostream& print_session_header(std::ostream& os) noexcept;
}; // namespace csv_parse;

// Template function definitions for defined substitutions

template<bool ForceQuot>
std::ostream& csv_parse::print_filtered_text(std::ostream& os, std::string const& text) noexcept
{
    for (auto bad_char : get_bad_chars())
    {
        if (text.find(bad_char) != text.npos)
        {
            return os << "\"" << text << "\"";
        }
    }
    
    return os << text;
}

template<>
std::ostream& csv_parse::print_filtered_text<true>(std::ostream& os, std::string const& text) noexcept
{
    return os << "\"" << text << "\"";
}

template<bool ForceQuot>
std::ostream& csv_parse::print_filtered_session(std::ostream& os, session_t const& session) noexcept
{
    // Print start time
    if (session.m_start_time.get() != nullptr) {
        // std::strftime doesn't seem to create the correct char string
        os << std::setfill('0') << std::setw(4)
           << session.m_start_time->tm_year + 1900
           << "-"
           << std::setfill('0') << std::setw(2)
           << session.m_start_time->tm_mon + 1
           << "-"
           << std::setfill('0') << std::setw(2)
           << session.m_start_time->tm_mday
           << " "
           << std::setfill('0') << std::setw(2)
           << session.m_start_time->tm_hour
           << ":"
           << std::setfill('0') << std::setw(2)
           << session.m_start_time->tm_min
           << csv_delimiter;
    }
    else
    {
        os << "N/A" << csv_delimiter;
    }
    // Print finish time
    if (session.m_finish_time.get() != nullptr) {
        os << std::setfill('0') << std::setw(4)
           << session.m_finish_time->tm_year + 1900
           << "-"
           << std::setfill('0') << std::setw(2)
           << session.m_finish_time->tm_mon + 1
           << "-"
           << std::setfill('0') << std::setw(2)
           << session.m_finish_time->tm_mday
           << " "
           << std::setfill('0') << std::setw(2)
           << session.m_finish_time->tm_hour
           << ":"
           << std::setfill('0') << std::setw(2)
           << session.m_finish_time->tm_min
           << csv_delimiter;
    }
    else
    {
        os << "N/A" << csv_delimiter;
    }
    // Print name
    csv_parse::print_filtered_text<ForceQuot>(os, session.m_name) << csv_delimiter;
    // Print labels
    std::stringstream labels_stream{};
    if (!session.m_labels.empty())
        csv_parse::print_filtered_text<ForceQuot>(labels_stream, session.m_labels.at(0));
    for (size_t idx = 1; idx < session.m_labels.size(); ++idx)
    {
        labels_stream << csv_delimiter;
        csv_parse::print_filtered_text<ForceQuot>(labels_stream, session.m_labels.at(idx));
    }
    print_filtered_text<ForceQuot>(os, labels_stream.str()) << csv_delimiter;
    // Print comment
    csv_parse::print_filtered_text<ForceQuot>(os, session.m_comment) << "\n";

    return os;
}

template<bool ForceQuot>
std::ostream& csv_parse::print_session_header(std::ostream& os) noexcept
{
    os << "Start time" << csv_delimiter
       << "Finish time" << csv_delimiter
       << "Name" << csv_delimiter
       << "Labels" << csv_delimiter
       << "Comment" << "\n";
    
    return os;
}

#endif // CL_PARSE_HPP_INCLUDED_