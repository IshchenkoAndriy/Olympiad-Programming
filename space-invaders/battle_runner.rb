require 'open3'

@app_candidate_1 = "spaceInvaders"
@app_candidate_2 = "spaceInvaders_old"

def generate_test
    count_of_columns = rand(1..100)
    start_position = rand(1..count_of_columns)
    
    input_data = "%d %d\n" % [count_of_columns, start_position]
    
    count_of_columns.times do
        input_data << " " << rand(1..100).to_s
    end
    
    input_data << "\n"
    input_data
end

def build (app_name)
  result = system "g++ %s.cpp -o %s -O2" % [app_name, app_name]
  if result
    puts "Build succeed."
  else
    puts "Build failed"
  end
  result
end

def test (data)
    result = false
    candidate_1_result = nil
    candidate_2_result = nil
    
    Open3.popen3("./#{@app_candidate_1}") {|stdin, stdout, stderr, wait_thr|
        stdin.write data
        candidate_1_result = stdout.read
    }
    
    Open3.popen3("./#{@app_candidate_2}") {|stdin, stdout, stderr, wait_thr|
        stdin.write data
        candidate_2_result = stdout.read
    }
    
    result = candidate_1_result.eql? candidate_2_result
    
    unless result then
        puts "Results don't match!!!"
        puts data
        puts "Result of %s is %s" % [@app_candidate_1, candidate_1_result]
        puts "Result of %s is %s" % [@app_candidate_2, candidate_2_result]
    end
    result
end

def run_testing
    10000.times do
        test generate_test
    end
end

run_testing if build(@app_candidate_1) and build(@app_candidate_2)