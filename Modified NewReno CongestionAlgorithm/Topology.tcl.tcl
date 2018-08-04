set ns [new Simulator]

LanRouter set debug_ 0

$ns color 1 blue
$ns color 2 green

set tr [open "out.tr" w]
$ns trace-all $tr

set nf [open "out.nam" w]
$ns namtrace-all $nf

proc finish { } {
  global ns nf tr
  $ns flush-trace
  close $nf
  close $tr
  exec nam out.nam &
  exit 0
}

for {set i 0} {$i<10} {incr i} {
	set n($i) [$ns node]
}
$ns duplex-link $n(2) $n(0) 10Mb 2ms DropTail
$ns duplex-link $n(3) $n(0) 10Mb 2ms DropTail
$ns duplex-link $n(4) $n(0) 10Mb 2ms DropTail
$ns duplex-link $n(5) $n(0) 10Mb 2ms DropTail

$ns duplex-link $n(0) $n(1) 1.5Mb 50ms DropTail

$ns duplex-link $n(1) $n(6) 10Mb 2ms DropTail
$ns duplex-link $n(1) $n(7) 10Mb 2ms DropTail
$ns duplex-link $n(1) $n(8) 10Mb 2ms DropTail
$ns duplex-link $n(1) $n(9) 10Mb 2ms DropTail

#$ns queue-limit $n(0) $n(1) 10

$ns duplex-link-op $n(2) $n(0) orient down
$ns duplex-link-op $n(3) $n(0) orient right-down
$ns duplex-link-op $n(4) $n(0) orient right-up
$ns duplex-link-op $n(5) $n(0) orient up

$ns duplex-link-op $n(0) $n(1) orient right

$ns duplex-link-op $n(1) $n(6) orient up
$ns duplex-link-op $n(1) $n(7) orient right-up
$ns duplex-link-op $n(1) $n(8) orient right-down
$ns duplex-link-op $n(1) $n(9) orient down

#$ns duplex-link-op $n(2) $n(3) queuePos 0.5

set tcpMain [new Agent/TCP/Vegas]
$tcpMain set class_ 1
$ns attach-agent $n(2) $tcpMain

set sinkMain [new Agent/TCPSink]
$ns attach-agent $n(9) $sinkMain
$ns connect $tcpMain $sinkMain
$tcpMain set fid_ 1

set ftpMain [new Application/FTP]
$ftpMain attach-agent $tcpMain
$ftpMain set type_ FTP

for {set i 0} {$i<5} {incr i} {
  set tcp($i) [new Agent/TCP/Vegas]
  $tcp($i) set class_ 1
  $ns attach-agent $n($i) $tcp($i)

  set sink($i) [new Agent/TCPSink]
  $ns attach-agent $n([expr 9-$i]) $sink($i)
  $ns connect $tcp($i) $sink($i)
  $tcp($i) set fid_ 2

  set ftp($i) [new Application/FTP]
  $ftp($i) attach-agent $tcp($i)
  $ftp($i) set type_ FTP
}

$ns at 0.1 "$ftpMain start"
for {set i 0} {$i<5} {incr i} {
$ns at 0.5 "$ftp($i) start"
}
$ns at 2 "$ftpMain stop"
for {set i 0} {$i<5} {incr i} {
$ns at 2.5 "$ftp($i) stop"
}
$ns at 2.8 "$ns detach-agent $n(2) $tcpMain ; $ns detach-agent $n(9) $sinkMain"
for {set i 0} {$i<5} {incr i} {
$ns at 2.9 "$ns detach-agent $n($i) $tcp($i) ; $ns detach-agent $n([expr 9-$i]) $sink($i)"
}
$ns at 3 "finish"

proc plotWindow {tcpSource outfile} {
  global ns
  set now [$ns now]
  set cwnd [$tcpSource set cwnd_]
  puts $outfile "$now $cwnd"
  $ns at [expr $now+0.1] "plotWindow $tcpSource $outfile"
}

set outfile [open "WinFileNewAlgo" w]

$ns at 0.0 "plotWindow $tcpMain $outfile"
$ns run
