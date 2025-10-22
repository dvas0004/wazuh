#include "utils/ipUtils.hpp"

#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <limits>
namespace utils::ip
{

uint32_t IPv4ToUInt(const std::string& ipStr)
{
    int a, b, c, d {};
    char z {}; // Character after IP
    uint32_t ipUInt = 0;

    if (sscanf(ipStr.c_str(), "%d.%d.%d.%d%c", &a, &b, &c, &d, &z) != 4)
    {
        throw std::invalid_argument("Invalid IPv4 address format");
    }
    else if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255)
    {
        throw std::invalid_argument("Invalid IPv4 address format");
    }

    ipUInt = a << 24;
    ipUInt |= b << 16;
    ipUInt |= c << 8;
    ipUInt |= d;

    return ipUInt;
}

// TODO: Missing unit tests fot this
uint32_t IPv4MaskUInt(const std::string& maskStr)
{

    uint32_t maskUInt = 0;

    if (maskStr.find('.') != std::string::npos)
    {
        // Thow an exception if the mask is not valid
        maskUInt = IPv4ToUInt(maskStr);
    }
    else
    {
        size_t afterMask = 0;
        // Thow an `invalid_argument` exception if the mask is not a number
        auto intMask = std::stoi(maskStr, &afterMask);
        if (intMask < 0 || intMask > 32)
        {
            throw std::invalid_argument("Invalid IPv4 mask format");
        }

        if (afterMask != maskStr.size())
        {
            throw std::invalid_argument("Invalid IPv4 mask format");
        }

        maskUInt = intMask == 0 ? 0 : 0xFFFFFFFF << (32 - intMask);
    }

    return maskUInt;
}

bool checkStrIsIPv4(const std::string& ip, std::array<uint8_t, 4>* outBytes)
{
    struct in_addr buf
    {
    };
    if (inet_pton(AF_INET, ip.c_str(), &buf) != 1)
        return false;

    if (outBytes)
        std::memcpy(outBytes->data(), &buf, outBytes->size());

    return true;
}

bool checkStrIsIPv6(const std::string& ip, std::array<uint8_t, 16>* outBytes)
{
    struct in6_addr buf
    {
    };
    if (inet_pton(AF_INET6, ip.c_str(), &buf) != 1)
        return false;

    if (outBytes)
        std::memcpy(outBytes->data(), &buf, outBytes->size());

    return true;
}

bool isSpecialIPv4Address(const std::string& ip)
{
    uint32_t ipUInt = IPv4ToUInt(ip);

    if ((ipUInt >= 0x0A000000 && ipUInt <= 0x0AFFFFFF)     // 10.x.x.x range
        || (ipUInt >= 0xAC100000 && ipUInt <= 0xAC1FFFFF)  // 172.16.x.x to 172.31.x.x
        || (ipUInt >= 0xC0A80000 && ipUInt <= 0xC0A8FFFF)  // 192.168.x.x range
        || (ipUInt >= 0x7F000000 && ipUInt <= 0x7FFFFFFF)) // 127.x.x.x loopback range

    {
        return true;
    }
    return false;
}

bool isSpecialIPv6Address(const std::string& ip)
{
    struct in6_addr addr;
    if (inet_pton(AF_INET6, ip.c_str(), &addr) != 1)
    {
        throw std::invalid_argument("Invalid IPv6 address");
    }

    return IN6_IS_ADDR_LOOPBACK(&addr)                              // Loopback
           || IN6_IS_ADDR_LINKLOCAL(&addr)                          // Link-local fe80::/10
           || (addr.s6_addr[0] == 0xFC || addr.s6_addr[0] == 0xFD); // ULA fc00::/7
}

const std::unordered_map<std::string_view, uint8_t>& IANA_PROTOCOL_NAME_TO_NUMBER()
{
    static const std::unordered_map<std::string_view, uint8_t> map = []
    {
        // Keep the cast to uint8_t safe if someone ever changes the table size.
        static_assert(IANA_NUMBER_TO_PROTOCOL_NAME_TABLE.size() <= (std::numeric_limits<uint8_t>::max() + 1u),
                      "IANA table size exceeds uint8_t range (0..255)");

        std::unordered_map<std::string_view, uint8_t> m;

        // Reserve precisely the number of non-empty entries.
        const auto nonEmpty = std::count_if(IANA_NUMBER_TO_PROTOCOL_NAME_TABLE.begin(),
                                            IANA_NUMBER_TO_PROTOCOL_NAME_TABLE.end(),
                                            [](std::string_view s) { return !s.empty(); });
        m.reserve(nonEmpty);

        // Use the container’s index type to avoid width/sign warnings.
        using index_t = decltype(IANA_NUMBER_TO_PROTOCOL_NAME_TABLE.size());
        for (index_t i = 0; i < IANA_NUMBER_TO_PROTOCOL_NAME_TABLE.size(); ++i)
        {
            std::string_view name = IANA_NUMBER_TO_PROTOCOL_NAME_TABLE[i];
            if (!name.empty())
                m.emplace(name, static_cast<uint8_t>(i));
        }
        return m;
    }();
    return map;
}

std::string normalizeIanaProtocolName(std::string_view in)
{
    std::string s(in);
    std::transform(s.begin(),
                   s.end(),
                   s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(static_cast<unsigned char>(c))); });
    for (char& c : s)
        if (c == '_' || std::isspace(static_cast<unsigned char>(c)))
            c = '-';
    // aliases -> canonical keys used in the table
    if (s == "icmpv6")
        s = "ipv6-icmp";
    if (s == "udp-lite")
        s = "udplite";
    if (s == "ip-in-ip")
        s = "ipip";
    return s;
}

std::optional<uint8_t> ianaProtocolNameToNumber(std::string_view name)
{
    const std::string key = normalizeIanaProtocolName(name);
    const auto& m = IANA_PROTOCOL_NAME_TO_NUMBER();
    if (auto it = m.find(key); it != m.end())
        return it->second;
    return std::nullopt;
}

std::optional<std::string_view> ianaProtocolNumberToName(uint8_t code)
{
    std::string_view s = IANA_NUMBER_TO_PROTOCOL_NAME_TABLE[code];
    if (s.empty())
        return std::nullopt;
    return s;
}

} // namespace utils::ip
