require "optparse"

device = path = nil
down = up = nil

op = OptionParser.new do |op|
  op.banner << " sha"

  op.on("-d", "--device name", String, "Name of the device to use") { |s| device = s }
  op.on("-f", "--file path", String, "Specific path to use") { |s| path = s }

  op.on("-D", "--down command", String, "Command to run when the button is pressed") { |s| down = s }
  op.on("-U", "--up command", String, "Command to run when the button is released") { |s| up = s }

  op.on("-h", "--help", "Print this message and exit") do
    $stderr.puts(op)
    exit
  end
end

op.parse(ARGV)

if device
  path = "/dev/#{device}"
end

if !path
  devices = Dir["/dev/cu.usbmodem*"]
  raise "no button detected" if devices.empty?
  raise "more than 1 button detected, please specify one" if devices.count > 1
  path = devices.first
end

file = File.open(path, "w+")

loop do
  raise "button disconnected" if (state = file.gets).nil?

  state.chomp!

  case state
  when "DOWN"
    system down if down
  when "UP"
    system up if up
  end
end
