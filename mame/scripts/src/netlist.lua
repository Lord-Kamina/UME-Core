-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

project "netlist"
	uuid "665ef8ac-2a4c-4c3e-a05f-fd1e5db11de9"
	kind (LIBTYPE)

	options {
		"ForceCPP",
	}

	includedirs {
		MAME_DIR .. "src/emu/netlist",
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/lib/util",
	}
	--	if _OPTIONS["with-bundled-expat"] then
	--	includedirs {
	--		MAME_DIR .. "3rdparty/expat/lib",
	--	}
	--end


	files {
		MAME_DIR .. "src/emu/netlist/nl_config.h",
		MAME_DIR .. "src/emu/netlist/nl_dice_compat.h",
		MAME_DIR .. "src/emu/netlist/nl_lists.h",
		MAME_DIR .. "src/emu/netlist/nl_time.h",
		MAME_DIR .. "src/emu/netlist/nl_util.h",
		MAME_DIR .. "src/emu/netlist/nl_base.c",
		MAME_DIR .. "src/emu/netlist/nl_base.h",
		MAME_DIR .. "src/emu/netlist/nl_parser.c",
		MAME_DIR .. "src/emu/netlist/nl_parser.h",
		MAME_DIR .. "src/emu/netlist/nl_setup.c",
		MAME_DIR .. "src/emu/netlist/nl_setup.h",
		MAME_DIR .. "src/emu/netlist/nl_factory.c",
		MAME_DIR .. "src/emu/netlist/nl_factory.h",
		MAME_DIR .. "src/emu/netlist/plib/pconfig.h",
		MAME_DIR .. "src/emu/netlist/plib/palloc.c",
		MAME_DIR .. "src/emu/netlist/plib/palloc.h",
		MAME_DIR .. "src/emu/netlist/plib/plists.h",
		MAME_DIR .. "src/emu/netlist/plib/poptions.h",
		MAME_DIR .. "src/emu/netlist/plib/pparser.c",
		MAME_DIR .. "src/emu/netlist/plib/pparser.h",
		MAME_DIR .. "src/emu/netlist/plib/pstate.c",
		MAME_DIR .. "src/emu/netlist/plib/pstate.h",
		MAME_DIR .. "src/emu/netlist/plib/pstring.c",
		MAME_DIR .. "src/emu/netlist/plib/pstring.h",
		MAME_DIR .. "src/emu/netlist/plib/pstring.c",
		MAME_DIR .. "src/emu/netlist/plib/pstring.h",
		MAME_DIR .. "src/emu/netlist/tools/nl_convert.c",
		MAME_DIR .. "src/emu/netlist/tools/nl_convert.h",
		MAME_DIR .. "src/emu/netlist/analog/nld_bjt.c",
		MAME_DIR .. "src/emu/netlist/analog/nld_bjt.h",
		MAME_DIR .. "src/emu/netlist/analog/nld_fourterm.c",
		MAME_DIR .. "src/emu/netlist/analog/nld_fourterm.h",
		MAME_DIR .. "src/emu/netlist/analog/nld_switches.c",
		MAME_DIR .. "src/emu/netlist/analog/nld_switches.h",
		MAME_DIR .. "src/emu/netlist/analog/nld_twoterm.c",
		MAME_DIR .. "src/emu/netlist/analog/nld_twoterm.h",
		MAME_DIR .. "src/emu/netlist/analog/nld_opamps.c",
		MAME_DIR .. "src/emu/netlist/analog/nld_opamps.h",
    MAME_DIR .. "src/emu/netlist/solver/nld_solver.c",
    MAME_DIR .. "src/emu/netlist/solver/nld_solver.h",
		MAME_DIR .. "src/emu/netlist/solver/nld_ms_direct.h",
		MAME_DIR .. "src/emu/netlist/solver/nld_ms_direct1.h",
		MAME_DIR .. "src/emu/netlist/solver/nld_ms_direct2.h",
		MAME_DIR .. "src/emu/netlist/solver/nld_ms_sor.h",
    MAME_DIR .. "src/emu/netlist/solver/nld_ms_sor_math.h",
    MAME_DIR .. "src/emu/netlist/solver/nld_ms_gmres.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_4020.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_4020.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_4066.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_4066.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7400.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7400.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7402.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7402.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7404.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7404.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7408.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7408.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7410.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7410.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7411.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7411.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7420.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7420.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7425.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7425.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7427.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7427.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7430.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7430.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7432.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7432.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7437.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7437.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7448.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7448.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7450.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7450.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7474.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7474.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7483.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7483.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7486.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7486.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7490.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7490.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_7493.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_7493.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_74107.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_74107.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_74123.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_74123.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_74153.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_74153.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_74175.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_74175.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_74192.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_74192.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_74193.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_74193.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_74279.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_74279.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_74ls629.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_74ls629.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_82S16.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_82S16.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_9310.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_9310.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_9312.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_9312.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_9316.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_9316.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_ne555.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_ne555.h",
    MAME_DIR .. "src/emu/netlist/devices/nld_mm5837.c",
    MAME_DIR .. "src/emu/netlist/devices/nld_mm5837.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_r2r_dac.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_r2r_dac.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_legacy.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_legacy.h",
		MAME_DIR .. "src/emu/netlist/devices/net_lib.c",
		MAME_DIR .. "src/emu/netlist/devices/net_lib.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_log.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_log.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_system.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_system.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_cmos.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_signal.h",
		MAME_DIR .. "src/emu/netlist/devices/nld_truthtable.c",
		MAME_DIR .. "src/emu/netlist/devices/nld_truthtable.h",
    MAME_DIR .. "src/emu/netlist/macro/nlm_ttl74xx.c",
    MAME_DIR .. "src/emu/netlist/macro/nlm_ttl74xx.h",
    MAME_DIR .. "src/emu/netlist/macro/nlm_cd4xxx.c",
    MAME_DIR .. "src/emu/netlist/macro/nlm_cd4xxx.h",
    MAME_DIR .. "src/emu/netlist/macro/nlm_opamp.c",
    MAME_DIR .. "src/emu/netlist/macro/nlm_opamp.h",
}