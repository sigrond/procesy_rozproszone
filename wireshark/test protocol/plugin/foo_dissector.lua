----------------------------------------
-- foo_dissector.lua
----------------------------------------


----------------------------------------
-- Version check
----------------------------------------
local major, minor, micro = get_version():match("(%d+)%.(%d+)%.(%d+)")

if major and tonumber(major) <= 1 and ((tonumber(minor) <= 10) or (tonumber(minor) == 11 and tonumber(micro) < 3)) then
        error(  "Sorry, but your Wireshark/Tshark version ("..get_version()..") is too old for this script!\n"..
                "This script needs Wireshark/Tshark version 1.11.3 or higher.\n" )
end

assert(ProtoExpert.new, "Wireshark does not have the ProtoExpert class, so it's too old - get the latest 1.11.3 or higher")


----------------------------------------
-- Foo Protocol port
----------------------------------------

local default_settings =
{
    port = 5555,
}

----------------------------------------
-- Foo Protocol fields definition
----------------------------------------

local foo = Proto("foo","Foo Protocol")

local codenames = 
{
    [0] = "Add",
    [1] = "Subtract",
    [2] = "Multiply",
    [3] = "Divide",
    [4] = "Result",
    [5] = "Error"
}

local pf_code   = ProtoField.uint8("foo.code", "Operation Code", base.DEC, codenames, 0x0F)
local pf_first  = ProtoField.int32("foo.first", "First Number")
local pf_second = ProtoField.int32("foo.second", "Second Number")

foo.fields = { pf_code, pf_first, pf_second}


local ef_too_short = ProtoExpert.new("foo.too_short.expert", "FOO message too short", expert.group.MALFORMED, expert.severity.ERROR)
local ef_bad_code  = ProtoExpert.new("foo.wrong_code", "Wrong FOO code", expert.group.MALFORMED, expert.severity.WARN)

foo.experts = { ef_too_short, ef_bad_code }

local FOO_HDR_LEN = 9

----------------------------------------
-- Dissection
----------------------------------------

function foo.dissector(tvbuf,pktinfo,root)

    pktinfo.cols.protocol:set("FOO")

    local pktlen = tvbuf:reported_length_remaining()

    local tree = root:add(foo, tvbuf:range(0,pktlen))

    if pktlen < FOO_HDR_LEN then
        tree:add_proto_expert_info(ef_too_short)
        return
    end

    tree:add(pf_code, tvbuf:range(0,1))
    local code = tvbuf:range(0,1):uint()
    
    tree:add_le(pf_first, tvbuf:range(1,4))
    local first = tvbuf:range(1,4):le_int()
    
    tree:add_le(pf_second, tvbuf:range(5,4))
    local second = tvbuf:range(5,4):le_int()
    
    if(code == 5) then
        pktinfo.cols.info:set(codenames[code])
    else 
        if (code < 5) then
            pktinfo.cols.info:set(codenames[code] .." " .. first .. " " .. second)
        else
            pktinfo.cols.info:set("Bad Code (" .. code ..")")
            
            tree:add_proto_expert_info(ef_bad_code)
        end
    end

    local pos = FOO_HDR_LEN

    return pos
end

----------------------------------------
-- Register Protocol
----------------------------------------

DissectorTable.get("tcp.port"):add(default_settings.port, foo)
