#ifndef JOB_HPP
#define JOB_HPP

#include <string>
#include <stdexcept>  // For exception handling

// Job class to represent an operating system job
class Job {
    private:
        std::string name;
        int length;
        int priority;

    public:
        // Constructor for Job, which accepts name, length, and priority

        Job() : name(""), length(0), priority(-20) {} // DEF CONSTRUCTOR
        // Constructor with validation
        Job(std::string jobName, int jobLength, int jobPriority)
            : name(jobName), length(0), priority(0) {
            // Validate job length (1 <= length <= 100)
            if (jobLength < 1 || jobLength > 100) {
                throw std::out_of_range("Job length must be between 1 and 100.");
            }
            length = jobLength;

            // Validate job priority (-20 <= priority <= 19)
            if (jobPriority < -20 || jobPriority > 19) {
                throw std::out_of_range("Job priority must be between -20 and 19.");
            }
            priority = jobPriority;
        }

        // Accessor methods
        std::string getName() const { return name; }
        int getLength() const { return length; }
        int getPriority() const { return priority; }
        void setLength(int len) {
            //if (jobDone()) return;
            if (len >= 0 && len <= 100) { 
                length = len;
            } 
            else {
                std::cout << "Invalid job duration.\n";
            }
            if (jobDone()) return;
            
        }
        bool jobDone() const { return length <= 0;}
};


#endif // JOB_HPP