require 'open3'

@app_name = "house"
@test_file_name_pattern = /#{@app_name}_test_\d+.txt/
@tests_dir = "tests"

def build
  result = system "g++ %s.cpp -o %s" % [@app_name, @app_name]
  if result
    puts "Build succeed."
  else
    puts "Build failed"
  end
  result
end

def test (test_file_name, result_file_name)
  result = false
  Open3.popen3("./#{@app_name}") {|stdin, stdout, stderr, wait_thr|
    stdin.write File.read("%s/%s" % [@tests_dir, test_file_name])
    result = File.read("%s/%s" % [@tests_dir, result_file_name]).eql? stdout.read
  }
  result
end

def run_testing
  all_files = Dir.entries(@tests_dir)
  
  all_files.each {|file_name|
    is_test = @test_file_name_pattern =~ file_name
    if is_test
      test_number = file_name.scan(/\d+/).first
      test_result_file_name = "#{@app_name}_result_#{test_number}.txt"
      
      if all_files.include? test_result_file_name
        puts "Test: #{test_number} Result: #{ test(file_name, test_result_file_name) ? "Passed" : "Failed" }"
      else
        puts "Result file for test #{test_number} not found."
      end
    end
  }
end

run_testing if build