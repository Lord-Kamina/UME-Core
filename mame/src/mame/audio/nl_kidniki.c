
#include "netlist/devices/net_lib.h"

#ifndef USE_FRONTIERS
#define USE_FRONTIERS 0
#endif

#ifndef USE_FIXED_STV
#define USE_FIXED_STV 0
#endif

/* ----------------------------------------------------------------------------
 *  Library section header START
 * ---------------------------------------------------------------------------*/

#ifndef __PLIB_PREPROCESSOR__

#define MC14584B_GATE(_name)                    		                      \
		NET_REGISTER_DEV(MC14584B_GATE, _name)

#define MC14584B_DIP(_name)            	        		                      \
		NET_REGISTER_DEV(MC14584B_DIP, _name)

#define LM324_DIP(_name)            			                              \
		NET_REGISTER_DEV(LM324_DIP, _name)

#define LM358_DIP(_name)            			                              \
		NET_REGISTER_DEV(LM358_DIP, _name)

NETLIST_EXTERNAL(kidniki_lib)

#endif

/* ----------------------------------------------------------------------------
 *  Library section header END
 * ---------------------------------------------------------------------------*/

/* ----------------------------------------------------------------------------
 *  Kidniki schematics
 * ---------------------------------------------------------------------------*/

NETLIST_START(kidniki_schematics)
	//  EESCHEMA NETLIST VERSION 1.1 (SPICE FORMAT) CREATION DATE: SAT 06 JUN 2015 01:06:26 PM CEST
	//  TO EXCLUDE A COMPONENT FROM THE SPICE NETLIST ADD [SPICE_NETLIST_ENABLED] USER FIELD SET TO: N
	//  TO REORDER THE COMPONENT SPICE NODE SEQUENCE ADD [SPICE_NODE_SEQUENCE] USER FIELD AND DEFINE SEQUENCE: 2,1,0
	// SHEET NAME:/
	// IGNORED O_AUDIO0: O_AUDIO0  49 0
	// .END

	LOCAL_SOURCE(kidniki_lib)
	INCLUDE(kidniki_lib)

	/*
	 * Workaround: The simplified opamp model does not correctly
	 * model the internals of the inputs.
	 */

	ANALOG_INPUT(VWORKAROUND, 2.061)
	RES(RWORKAROUND, RES_K(27))
	NET_C(VWORKAROUND.Q, RWORKAROUND.1)
	NET_C(XU1.6, RWORKAROUND.2)

	CAP(C200, CAP_N(100))
	CAP(C28, CAP_U(1))
	CAP(C31, CAP_N(470))
	CAP(C32, CAP_N(3.3))
	CAP(C33, CAP_U(1))
	CAP(C34, CAP_N(1))
	CAP(C35, CAP_N(1))
	CAP(C36, CAP_N(6.5))
	CAP(C37, CAP_N(22))
	CAP(C38, CAP_N(1))
	CAP(C39, CAP_N(1))
	CAP(C40, CAP_P(12))
	CAP(C41, CAP_U(1))
	CAP(C42, CAP_N(1.2))
	CAP(C43, CAP_N(1.2))
	CAP(C44, CAP_U(1))
	CAP(C45, CAP_N(22))
	CAP(C47, CAP_U(1))
	CAP(C48, CAP_N(470))
	CAP(C49, CAP_N(3.3))
	CAP(C50, CAP_N(22))
	CAP(C51, CAP_N(22))
	CAP(C52, CAP_N(27))
	CAP(C53, CAP_N(27))
	CAP(C56, CAP_N(6.8))
	CAP(C57, CAP_N(6.8))
	CAP(C59, CAP_N(6.8))
	CAP(C60, CAP_N(22))
	CAP(C61, CAP_N(22))
	CAP(C62, CAP_N(6.8))
	CAP(C63, CAP_N(1))
	CAP(C64, CAP_N(68))
	CAP(C65, CAP_N(68))
	CAP(C66, CAP_N(68))
	CAP(C67, CAP_N(15))
	CAP(C68, CAP_N(15))
	CAP(C69, CAP_N(10))
	CAP(C70, CAP_N(22))
	CAP(C72, CAP_N(12))
	CAP(C73, CAP_N(10))
	CAP(C76, CAP_N(68))
	CAP(C77, CAP_N(12))

	DIODE(D3, "1S1588")
	DIODE(D4, "1S1588")
	DIODE(D5, "1S1588")

	POT(RV1, RES_K(50))

	QBJT_EB(Q10, "2SC945")
	QBJT_EB(Q3, "2SC945")
	QBJT_EB(Q4, "2SC945")
	QBJT_EB(Q5, "2SC945")
	QBJT_EB(Q6, "2SC945")
	QBJT_EB(Q7, "2SC945")
	QBJT_EB(Q9, "2SC945")

	LM324_DIP(XU1)
	LM358_DIP(XU2)
	//SUBMODEL(LM324_DIP,XU1)
	//SUBMODEL(LM358_DIP,XU2)

	MC14584B_DIP(XU3)

	RES(R100, RES_K(560))
	RES(R101, RES_K(150))
	RES(R102, RES_K(150))
	RES(R103, RES_K(470))
	RES(R104, RES_K(22))
	RES(R105, RES_K(470))
	RES(R106, RES_K(150))
	RES(R107, RES_K(150))
	RES(R108, RES_K(560))
	RES(R119, RES_K(22))
	RES(R200, RES_K(100))
	RES(R201, RES_K(100))
	RES(R27, RES_K(6.8))
	RES(R28, RES_K(150))
	RES(R29, RES_K(2.7))
	RES(R30, RES_K(10))
	RES(R31, RES_K(5.1))
	//RES(R32, RES_K(1))
	RES(R32, RES_K(4.7))
	RES(R34, RES_K(100))
	RES(R35, RES_K(100))
	RES(R36, RES_K(100))
	RES(R37, RES_K(47))
	RES(R38, 820)
	RES(R39, RES_K(22))
	RES(R40, RES_K(10))
	RES(R41, RES_K(10))
	RES(R42, RES_K(150))
	RES(R43, 470)
	RES(R44, RES_K(100))
	RES(R45, RES_K(1))
	RES(R46, RES_K(12))
	RES(R48, 470)
	RES(R48_2, RES_K(100))
	RES(R49, RES_K(10))
	RES(R50, RES_K(2.2))
	RES(R51, RES_K(150))
	RES(R52, RES_K(100))
	RES(R53, RES_K(100))
	RES(R54, RES_K(680))
	RES(R55, RES_K(510))
	RES(R57, 560)
	RES(R58, RES_K(39))
	RES(R59, 560)
	RES(R60, RES_K(39))
	RES(R61, RES_K(100))
	RES(R62, RES_K(100))
	RES(R63, RES_K(1))
	RES(R65, RES_K(1))
	RES(R65_1, RES_K(27))
	RES(R66, RES_M(1))
	RES(R67, RES_K(100))
	RES(R68, RES_K(100))
	RES(R69, RES_K(1))
	RES(R70, RES_K(10))
	RES(R71, RES_K(100))
	RES(R72, RES_K(100))
	RES(R73, RES_K(10))
	RES(R74, RES_K(10))
	RES(R75, RES_K(10))
	RES(R76, RES_K(10))
	RES(R81, 220)
	RES(R82, RES_M(2.2))
	RES(R83, RES_K(12))
	RES(R84, RES_K(1))
	RES(R85, RES_M(2.2))
	RES(R86, RES_K(10))
	RES(R87, RES_K(68))
	RES(R89, RES_K(22))
	RES(R90, RES_K(390))
	RES(R91, RES_K(100))
	RES(R92, RES_K(22))
	RES(R93, RES_K(1))
	RES(R94, RES_K(22))
	RES(R95, RES_K(330))
	RES(R96, RES_K(150))
	RES(R97, RES_K(150))
	RES(R98, RES_K(650))

	#if USE_FIXED_STV
	ANALOG_INPUT(STV, 2)
	#else
	RES(R78, RES_K(3.3))
	RES(R77, RES_K(2.2))
	CAP(C58, CAP_U(47))
	#endif

	NET_C(R95.1, XU3.2, R96.2)
	NET_C(R95.2, XU3.1, C69.1)
	NET_C(XU3.3, R103.2, C73.1)
	NET_C(XU3.4, R103.1, R102.2)
	NET_C(XU3.5, R105.2, C72.1)
	NET_C(XU3.6, R105.1, R106.2)
	#if USE_FIXED_STV
	//FIXME: We should have a NET_C_REMOVE
	NET_C(/*XU3.7,*/ C69.2, C73.2, C72.2, C77.2, C67.2, C68.2, R65.2, R38.2, XU1.11, R54.2, Q4.E, R63.2, C47.2, R72.2, R67.2, R71.2, R68.2, C48.2, R46.2, C28.1, C32.1, R43.2, XU2.4, C56.1, C52.1,/* R77.2, C58.1, */ R48.2, R93.2, R94.2, R119.2, R104.2, R53.2, R34.2, R81.2, R92.2, R89.2, C33.1, R37.2, R36.1, R91.1, I_V0.Q, RV1.3)
	#else
	NET_C(/*XU3.7,*/ C69.2, C73.2, C72.2, C77.2, C67.2, C68.2, R65.2, R38.2, XU1.11, R54.2, Q4.E, R63.2, C47.2, R72.2, R67.2, R71.2, R68.2, C48.2, R46.2, C28.1, C32.1, R43.2, XU2.4, C56.1, C52.1, R77.2, C58.1, R48.2, R93.2, R94.2, R119.2, R104.2, R53.2, R34.2, R81.2, R92.2, R89.2, C33.1, R37.2, R36.1, R91.1, I_V0.Q, RV1.3)
	#endif
	NET_C(XU3.8, R108.1, R107.2)
	NET_C(XU3.9, R108.2, C77.1)
	NET_C(XU3.10, R100.1, R101.2)
	NET_C(XU3.11, R100.2, C67.1)
	NET_C(XU3.12, R98.1, R97.2)
	NET_C(XU3.13, R98.2, C68.1)
	#if USE_FIXED_STV
	NET_C(/*XU3.14,*/ XU1.4, R66.1, R70.1, Q6.C, Q5.C, XU2.8, /* R78.1, */ R86.1, R83.1, Q3.C, I_V5.Q)
	#else
	NET_C(/*XU3.14,*/ XU1.4, R66.1, R70.1, Q6.C, Q5.C, XU2.8, R78.1, R86.1, R83.1, Q3.C, I_V5.Q)
	#endif
	NET_C(R96.1, R102.1, R106.1, R107.1, R101.1, R97.1, R65.1, C63.2)
	NET_C(C63.1, R65_1.2)
	NET_C(R65_1.1, R44.2, C38.2, C40.2, XU1.6)
	#if USE_FIXED_STV
	NET_C(R30.1, R41.1, R40.1, STV, R76.2, /* R78.2, R77.1, C58.2*/ STV)
	#else
	NET_C(R30.1, R41.1, R40.1, R76.2, R78.2, R77.1, C58.2)
	#endif
	NET_C(R30.2, XU1.5)
	NET_C(R44.1, C39.1, C40.1, R48_2.2)
	NET_C(C38.1, C39.2, R38.1)
	NET_C(XU1.1, XU1.2, R39.1, R32.2)
	NET_C(XU1.3, C34.1, R41.2)
	NET_C(XU1.7, R45.2)
	NET_C(XU1.8, XU1.9, R31.2, C36.2)
	NET_C(XU1.10, R42.1, C32.2)
	NET_C(XU1.12, C49.1, C31.1, R40.2, C61.1, C60.1)
	NET_C(XU1.13, R27.1, R28.2)
	NET_C(XU1.14, R28.1, R29.2, I_SINH0)
	NET_C(R48_2.1, C45.2, R54.1)
	NET_C(C45.1, R55.1, Q7.B)
	NET_C(R55.2, R90.2, C33.2, R37.1, Q3.E)
	NET_C(R45.1, C44.2)
	NET_C(C44.1, R66.2, Q4.B)
	NET_C(Q4.C, C42.1, C43.1, R46.1, C35.2, D4.K, D5.K)
	NET_C(R70.2, R69.2, Q7.C)
	NET_C(R63.1, Q7.E)
	NET_C(R69.1, C49.2)
	NET_C(C42.2, R58.1, D5.A)
	NET_C(R58.2, R57.1, C47.1)
	NET_C(R57.2, Q6.E)
	NET_C(Q6.B, R61.1)
	NET_C(C50.1, R67.1, R61.2)
	NET_C(C50.2, R72.1, I_OH0.Q)
	NET_C(C51.1, R68.1, R62.2)
	NET_C(C51.2, R71.1, I_CH0.Q)
	NET_C(R62.1, Q5.B)
	NET_C(Q5.E, R59.2)
	NET_C(R60.1, C43.2, D4.A)
	NET_C(R60.2, R59.1, C48.1)
	NET_C(C35.1, C34.2, R39.2)
	NET_C(R32.1, C31.2)
	NET_C(R27.2, C28.2)
	NET_C(R29.1, R31.1, R50.2, R49.1, RV1.1)
	NET_C(R42.2, R51.1, C36.1)
	NET_C(R51.2, C41.1)
	NET_C(C41.2, R43.1, I_SOUNDIC0)
	NET_C(XU2.1, XU2.2, R73.1)
	NET_C(XU2.3, R76.1, C200.2)
	NET_C(XU2.5, C56.2, R75.1)
	NET_C(XU2.6, XU2.7, R50.1, C53.2)
	NET_C(R75.2, R74.1, C53.1)
	NET_C(R74.2, C52.2, R73.2)
	NET_C(R49.2, R48.1, I_SOUND0)
	NET_C(Q9.E, R81.1)
	NET_C(Q9.C, R84.2, R83.2, R82.1, C59.1)
	NET_C(Q9.B, R82.2, C62.1)
	NET_C(Q10.E, R93.1)
	NET_C(Q10.C, R87.2, R86.2, R85.1, C76.1)
	NET_C(Q10.B, R85.2, C64.1)
	NET_C(R84.1, C61.2)
	NET_C(C60.2, R87.1)
	NET_C(C64.2, C65.1, R94.1, D3.K)
	NET_C(C65.2, C66.1, R119.1)
	NET_C(C66.2, C76.2, R104.1)
	NET_C(R53.1, R52.2, C37.1)
	NET_C(R34.1, C37.2, I_BD0.Q)
	NET_C(R52.1, D3.A)
	NET_C(R92.1, C62.2, C57.1)
	NET_C(R89.1, C57.2, C59.2, R90.1)
	NET_C(Q3.B, R35.1)
	NET_C(R35.2, R36.2, C70.1)
	NET_C(R91.2, C70.2, I_SD0.Q)
	NET_C(I_MSM3K0.Q, R200.2)
	NET_C(I_MSM2K0.Q, R201.2)
	NET_C(R200.1, R201.1, C200.1)

	/* Amplifier stage */

	CAP(C26, CAP_U(1))
	RES(R25, 560)
	RES(R26, RES_K(47))
	CAP(C29, CAP_U(0.01))

	NET_C(RV1.2, C26.1)
	NET_C(C26.2, R25.1)
	NET_C(R25.2, R26.1, C29.1)
	NET_C(R26.2, C29.2, GND)

NETLIST_END()

/* ----------------------------------------------------------------------------
 *  Library section body START
 * ---------------------------------------------------------------------------*/

NETLIST_START(opamp)

	/* Opamp model from
	 *
	 * http://www.ecircuitcenter.com/Circuits/opmodel1/opmodel1.htm
	 *
	 * Bandwidth 1Mhz
	 *
	 */

	/* Terminal definitions for calling netlists */

	ALIAS(PLUS, G1.IP) // Positive input
	ALIAS(MINUS, G1.IN) // Negative input
	ALIAS(OUT, EBUF.OP) // Opamp output ...

	ALIAS(GND, EBUF.ON) // GND terminal
	ALIAS(VCC, DUMMY.I) // VCC terminal
	DUMMY_INPUT(DUMMY)

	/* The opamp model */

	VCCS(G1)
	PARAM(G1.RI, RES_K(1000))
#if 1
	PARAM(G1.G, 100)  // typical OP-AMP amplification 100 * 1000 = 100000
	RES(RP1, 1000)
	CAP(CP1, 1.59e-5)   // <== change to 1.59e-3 for 10Khz bandwidth
#else
	PARAM(G1.G, 1)  // typical OP-AMP amplification 100 * 1000 = 100000
	RES(RP1, 100000)
	CAP(CP1, 1.59e-7)   // <== change to 1.59e-3 for 10Khz bandwidth
#endif
	VCVS(EBUF)
	PARAM(EBUF.RO, 50)
	PARAM(EBUF.G, 1)

//    PARAM(EBUF.RI, 1e20)
//    NET_C(EBUF.ON, GND)

	NET_C(G1.ON, GND)
	NET_C(RP1.2, GND)
	NET_C(CP1.2, GND)
	NET_C(EBUF.IN, GND)

	NET_C(RP1.1, G1.OP)
	NET_C(CP1.1, RP1.1)

	DIODE(DP,"1N914")
	DIODE(DN,"1N914")

	NET_C(DP.K, VCC)
#if 1
	NET_C(DP.A, DN.K, RP1.1)
#else
	RES(RDP, 1000)
	RES(RDN, 1000)
	NET_C(RDP.1, DP.A)
	NET_C(RDN.1, DN.K)
	NET_C(RDP.2, RDN.2, RP1.1)
#endif
	NET_C(DN.A, GND)

	NET_C(EBUF.IP, RP1.1)

NETLIST_END()

NETLIST_START(LM324_DIP)
	SUBMODEL(opamp, op1)
	SUBMODEL(opamp, op2)
	SUBMODEL(opamp, op3)
	SUBMODEL(opamp, op4)

	ALIAS( 1, op1.OUT)
	ALIAS( 2, op1.MINUS)
	ALIAS( 3, op1.PLUS)

	ALIAS( 7, op2.OUT)
	ALIAS( 6, op2.MINUS)
	ALIAS( 5, op2.PLUS)

	ALIAS( 8, op3.OUT)
	ALIAS( 9, op3.MINUS)
	ALIAS(10, op3.PLUS)

	ALIAS(14, op4.OUT)
	ALIAS(13, op4.MINUS)
	ALIAS(12, op4.PLUS)

	NET_C(op1.GND, op2.GND, op3.GND, op4.GND)
	NET_C(op1.VCC, op2.VCC, op3.VCC, op4.VCC)

	ALIAS(11, op1.GND)
	ALIAS( 4, op1.VCC)
NETLIST_END()

NETLIST_START(LM358_DIP)
	SUBMODEL(opamp, op1)
	SUBMODEL(opamp, op2)

	ALIAS( 1, op1.OUT)
	ALIAS( 2, op1.MINUS)
	ALIAS( 3, op1.PLUS)

	ALIAS( 7, op2.OUT)
	ALIAS( 6, op2.MINUS)
	ALIAS( 5, op2.PLUS)


	NET_C(op1.GND, op2.GND)
	NET_C(op1.VCC, op2.VCC)

	ALIAS( 4, op1.GND)
	ALIAS( 8, op1.VCC)
NETLIST_END()

NETLIST_START(MC14584B_DIP)
	MC14584B_GATE(s1)
	MC14584B_GATE(s2)
	MC14584B_GATE(s3)
	MC14584B_GATE(s4)
	MC14584B_GATE(s5)
	MC14584B_GATE(s6)

	ALIAS( 1, s1.A)
	ALIAS( 2, s1.Q)
	ALIAS( 3, s2.A)
	ALIAS( 4, s2.Q)
	ALIAS( 5, s3.A)
	ALIAS( 6, s3.Q)

	ALIAS( 8, s4.Q)
	ALIAS( 9, s4.A)
	ALIAS(10, s5.Q)
	ALIAS(11, s5.A)
	ALIAS(12, s6.Q)
	ALIAS(13, s6.A)
NETLIST_END()

NETLIST_START(kidniki_lib)
	TRUTHTABLE_START(MC14584B_GATE, 1, 1, 0, "")
		TT_HEAD(" A | Q ")
		TT_LINE(" 0 | 1 |100")
		TT_LINE(" 1 | 0 |100")
		TT_FAMILY("MC14584B FAMILY(IVL=2.1 IVH=2.7 OVL=0.05 OVH=4.95 ORL=10.0 ORH=10.0)")
	TRUTHTABLE_END()

	LOCAL_LIB_ENTRY(LM324_DIP)
	LOCAL_LIB_ENTRY(LM358_DIP)
	LOCAL_LIB_ENTRY(MC14584B_DIP)

NETLIST_END()
