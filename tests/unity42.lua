#!/usr/local/bin/lua

local commands = {}
local success = 0
local fail = 0
local timedout = 0
local crashed = 0

local success_cmd = {}
local failed_cmd = {}
local timedout_cmd = {}
local crash_cmd = {}

local timeout = 2


local function print_crash(txt)
    local index = #crash_cmd > 0 and #crash_cmd or 1
    crash_cmd[index] = crash_cmd[index] or {}
    crash_cmd[index][#crash_cmd[index] + 1] = txt
end

local function print_timeout(txt)
    local index = #timedout_cmd > 0 and #timedout_cmd or 1
    timedout_cmd[index] = timedout_cmd[index] or {}
    timedout_cmd[index][#timedout_cmd[index] + 1] = txt
end

local function print_fail(txt)
    local index = #failed_cmd > 0 and #failed_cmd or 1
    failed_cmd[index] = failed_cmd[index] or {}
    failed_cmd[index][#failed_cmd[index] + 1] = txt
end

local function print_success(txt)
    local index = #success_cmd > 0 and #success_cmd or 1
    success_cmd[index] = success_cmd[index] or {}
    success_cmd[index][#success_cmd[index] + 1] = txt
end

local function stringify(txt)
    return txt:gsub("\\", "\\\\"):gsub('"', '\\"')
end

local function popen(process)
    local errfile = os.tmpname()

    local proc = io.popen("/bin/echo -E \"("..stringify(process)..") 2> "..errfile.."\" | bash", "r")
    local errh = io.open(errfile, "r")
    local funcs = {}
    function funcs.close(self)
        local meta = getmetatable(self)
        meta.__err:close()
        os.remove(meta.__errfile)
        return meta.__proc:close()
    end
    function funcs.flush(self, ...)
        local meta = getmetatable(self)

        meta.__proc:flush()
    end
    function funcs.readOut(self, ...)
        local meta = getmetatable(self)

        return meta.__proc:read(...)
    end
    function funcs.read(self, ...)
        local meta = getmetatable(self)

        return meta.__proc:read(...)..meta.__err:read(...)
    end
    function funcs.readErr(self, ...)
        local meta = getmetatable(self)

        return meta.__err:read(...)
    end
    return setmetatable({}, {
        __index = funcs,
        __proc = proc,
        __err = errh,
        __errfile = errfile,
    })
end

function execute_tcsh(command)
    local shell = popen("timeout "..timeout.."s ./42sh <<< \""..stringify(command).."\"", "r")
    local shell_out
    local shell_code = 0
    local tcsh_code = 0
    if shell then
        shell_out = shell:read("*all")
        if shell_out:sub(#shell_out, #shell_out) == "\n" then
            shell_out = shell_out:sub(1, #shell_out - 1)
        end
        _, _, shell_code = shell:close()
    else
        print_fail("\x1B[0m[\x1B[31;1mERROR\x1B[0m] Cannot find shell '42sh'")
        return false
    end

    local tcsh = popen("timeout "..timeout.."s tcsh <<< \""..stringify(command).."\"", "r")
    local tcsh_out
    if tcsh then
        tcsh_out = tcsh:read("*all")
        if tcsh_out:sub(#tcsh_out, #tcsh_out) == "\n" then
            tcsh_out = tcsh_out:sub(1, #tcsh_out - 1)
        end
        _, _, tcsh_code = tcsh:close()
    else
        print_fail("\x1B[0m[\x1B[31;1mERROR\x1B[0m] Cannot find shell 'tcsh'")
        return false
    end

    if tcsh_out == shell_out and shell_code == tcsh_code then
        success = success + 1
        print_success("\x1B[0m[\x1B[32;1mSUCCESS\x1B[0m] \x1B[33;1m"..command)
        print_success("\x1B[33;1m[\x1B[0m\x1B[36;1mExit Code \x1B[32;1m"..shell_code.."\x1B[0m\x1B[33;1m]\x1B[0m")
    else
        local diag_tcsh = "\x1B[0m"
        local diag_shell = "\x1B[0m"
        local mx = #shell_out > #tcsh_out and shell_out or tcsh_out
        local mn = #shell_out < #tcsh_out and shell_out or tcsh_out
        local eq = true
        for i=1, #mx do
            local check = mx:sub(i, i) == mn:sub(i, i)
            if check ~= eq then
                if check then
                    diag_tcsh = diag_tcsh.."\x1B[0m"
                    diag_shell = diag_shell.."\x1B[0m"
                else
                    diag_tcsh = diag_tcsh.."\x1B[31;1m"
                    diag_shell = diag_shell.."\x1B[31;1m"
                end
            end
            diag_tcsh = diag_tcsh..tcsh_out:sub(i, i)
            diag_shell = diag_shell..shell_out:sub(i, i)
            eq = check
        end
        local color = shell_code == tcsh_code and "\x1B[32;1m" or "\x1B[31;1m"
        if shell_code == 124 or tcsh_code == 124 then
            timedout = timedout + 1
            print_timeout("\x1B[0m[\x1B[35;1mTIMEOUT\x1B[0m] \x1B[33;1m"..command.." ::")
        else
            if shell_out:match("Segmentation Fault") then
                crashed = crashed + 1
                print_crash("\x1B[0m[\x1B[31mCRASH\x1B[0m] \x1B[33;1m"..command.." ::")
                print_crash("\x1B[0m\x1B[33m==== Expected [TCSH] ====\x1B[0m")
                print_crash(diag_tcsh.."\x1B[0m")
                print_crash("\x1B[33;1m[\x1B[0m\x1B[36;1mExit Code "..color..tcsh_code.."\x1B[0m\x1B[33;1m]\x1B[0m")
                print_crash("\x1B[33m==== GOT [42SH] ====\x1B[0m")
                print_crash(diag_shell.."\x1B[0m")
                print_crash("\x1B[33;1m[\x1B[0m\x1B[36;1mExit Code "..color..shell_code.."\x1B[0m\x1B[33;1m]\x1B[0m")
            else
                fail = fail + 1
                print_fail("\x1B[0m[\x1B[31;1mFAIL\x1B[0m] \x1B[33;1m"..command.." ::")
                print_fail("\x1B[0m\x1B[33m==== Expected [TCSH] ====\x1B[0m")
                print_fail(diag_tcsh.."\x1B[0m")
                print_fail("\x1B[33;1m[\x1B[0m\x1B[36;1mExit Code "..color..tcsh_code.."\x1B[0m\x1B[33;1m]\x1B[0m")
                print_fail("\x1B[33m==== GOT [42SH] ====\x1B[0m")
                print_fail(diag_shell.."\x1B[0m")
                print_fail("\x1B[33;1m[\x1B[0m\x1B[36;1mExit Code "..color..shell_code.."\x1B[0m\x1B[33;1m]\x1B[0m")
            end
        end
    end
end

function execute_out(command, file)
    local shell = popen("timeout "..timeout.."s ./42sh <<< \""..stringify(command).."\"", "r")
    local shell_out
    if shell then
        shell_out = shell:read("*all")
        if shell_out:sub(#shell_out, #shell_out) == "\n" then
            shell_out = shell_out:sub(1, #shell_out - 1)
        end
        shell:close()
    else
        print_fail("\x1B[0m[\x1B[31;1mERROR\x1B[0m] Cannot find shell '42sh'")
        return false
    end

    local out_handle = io.open("tests/tests_out/"..file, "r")
    local out
    if out_handle then
        out = out_handle:read("*all")
        if out:sub(#out, #out) == "\n" then
            out = out:sub(1, #out - 1)
        end
        out_handle:close()
    else
        print_fail("\x1B[0m[\x1B[31;1mERROR\x1B[0m] Cannot find shell '\x1B[33;1mtests/tests_out/"..file.."'\x1B[0m")
        return false
    end

    if out == shell_out then
        success = success + 1
        print_success("\x1B[0m[\x1B[32;1mSUCCESS\x1B[0m] \x1B[33;1m"..command)
    else
        local diag_out = "\x1B[0m"
        local diag_shell = "\x1B[0m"
        local mx = #shell_out > #out and shell_out or out
        local mn = #shell_out < #out and shell_out or out
        local eq = true
        for i=1, #mx do
            local check = mx:sub(i, i) == mn:sub(i, i)
            if check ~= eq then
                if check then
                    diag_out = diag_out.."\x1B[0m"
                    diag_shell = diag_shell.."\x1B[0m"
                else
                    diag_out = diag_out.."\x1B[31;1m"
                    diag_shell = diag_shell.."\x1B[31;1m"
                end
            end
            diag_out = diag_out..out:sub(i, i)
            diag_shell = diag_shell..shell_out:sub(i, i)
            eq = check
        end
        if shell_out:match("Segmentation Fault") then
            crashed = crashed + 1
            print_crash("\x1B[0m[\x1B[31mCRASH\x1B[0m] \x1B[33;1m"..command.." ::")
            print_crash("\x1B[0m\x1B[33m==== Expected ["..file.."] ====\x1B[0m")
            print_crash(diag_out.."\x1B[0m")
            print_crash("\x1B[33m==== GOT [42SH] ====\x1B[0m")
            print_crash(diag_shell.."\x1B[0m")
        else
            fail = fail + 1
            print_fail("\x1B[0m[\x1B[31;1mFAIL\x1B[0m] \x1B[33;1m"..command.." ::")
            print_fail("\x1B[0m\x1B[33m==== Expected ["..file.."] ====\x1B[0m")
            print_fail(diag_out.."\x1B[0m")
            print_fail("\x1B[33m==== GOT [42SH] ====\x1B[0m")
            print_fail(diag_shell.."\x1B[0m")
        end
    end
end


local handle = io.open("tests/tests", "r")
if handle then
    local line = handle:read()
    while line do
        if line:sub(1,1) ~= "#" then
            local cmd, file = line:match("([^:]+):[ ]*(.+)")
            if cmd and file then
                commands[#commands + 1] = {cmd, file}
            end
        end
        line = handle:read()
    end
    handle:close()
    print("\n\n\n")
    print("\x1B[32;1m===================================================")
    print("\x1B[32;1m=                \x1B[33;1mFUNCTIONNAL TESTS                \x1B[32;1m=")
    print("\x1B[32;1m===================================================\x1B[0m")
    local sh42 = io.open("./42sh", "r")
    if sh42 then
        sh42:close()
    else
        print("\x1B[31;1mFile not found '42sh'\x1B[0m")
        os.exit(84)
    end

    local bar_size = "========================================================================================="
    for i=1, #commands do
        print("\x1B[35;1mExecuting: \x1B[0m\x1B[33;1m"..commands[i][1].."\x1B[0m")
        if commands[i][2] == "tcsh" then
            execute_tcsh(commands[i][1])
        else
            execute_out(commands[i][1], commands[i][2])
        end
        success_cmd[#success_cmd + 1] = {}
        failed_cmd[#failed_cmd + 1] = {}
        timedout_cmd[#timedout_cmd + 1] = {}
        crash_cmd[#crash_cmd + 1] = {}
    end

    for i=1, #commands do
        if success_cmd[i] and #success_cmd[i] > 0 then
            print("\x1B[0m\x1B[34m"..bar_size.."\x1B[0m")
            for j=1, #success_cmd[i] do
                print(success_cmd[i][j])
            end
        end
    end

    for i=1, #commands do
        if timedout_cmd[i] and #timedout_cmd[i] > 0 then
            print("\x1B[0m\x1B[34m"..bar_size.."\x1B[0m")
            for j=1, #timedout_cmd[i] do
                print(timedout_cmd[i][j])
            end
        end
    end

    for i=1, #commands do
        if failed_cmd[i] and #failed_cmd[i] > 0 then
            print("\x1B[0m\x1B[34m"..bar_size.."\x1B[0m")
            for j=1, #failed_cmd[i] do
                print(failed_cmd[i][j])
            end
        end
    end

    for i=1, #commands do
        if crash_cmd[i] and #crash_cmd[i] > 0 then
            print("\x1B[0m\x1B[34m"..bar_size.."\x1B[0m")
            for j=1, #crash_cmd[i] do
                print(crash_cmd[i][j])
            end
        end
    end

    local percent = (math.floor(success / #commands * 10000) / 100)
    local diag = "= Total: "..#commands.." | Success: "..success.." | Fails: "..fail.." | Crashs: "..crashed.." | Timeouts: "..timedout.." | SuccessRate: "..percent.."%"
    local color = "\x1B[31;1m"
    if percent < 50 then
        color = "\x1B[31;1m"
    elseif percent < 75 then
        color = "\x1B[33m"
    else
        color = "\x1B[32;1m"
    end
    local diag_f = "= \x1B[0mTotal: \x1B[36;1m"..#commands.." \x1B[34m| \x1B[0mSuccess: \x1B[32;1m"..success.." \x1B[34m| \x1B[0mFails: \x1B[31;1m"..fail.."\x1B[0m | Crashs: \x1B[31m"..crashed.."\x1B[0m | Timeouts: \x1B[35;1m"..timedout.."\x1B[0m | SuccessRate: "..color..percent.."%"
    print("\x1B[0m\x1B[34m"..bar_size.."\x1B[0m")
    print("\x1B[0m\x1B[34m"..diag_f..string.rep(" ", #bar_size - #diag - 1).."\x1B[34m=")
    print("\x1B[0m\x1B[34m"..bar_size.."\x1B[0m")
else
    print("\x1B[31;1mFile not found 'tests'\x1B[0m")
    os.exit(84)
end