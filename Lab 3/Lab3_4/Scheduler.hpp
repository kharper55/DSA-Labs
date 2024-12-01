#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "HeapPriorityQueue.hpp"
#include "JobComparator.hpp"        // For custom comparator object and Job object

class Scheduler {
private:
    HeapPriorityQueue<Job, JobComparator> jobQueue; // Priority queue for jobs

public:
    // Add a job to the queue
    void addJob(const std::string& name, int length, int priority) {
        Job newJob(name, length, priority);  // Create the job
        jobQueue.insert(newJob);             // Insert the job into the priority queue
    }

    // Run the scheduler for one time slice
    void runTimeSlice() {
        if (!jobQueue.empty()) {
            // Get the highest priority job
            Job currentJob = jobQueue.root();
            jobQueue.removeRoot();

            // Simulate the job running for its full length
            std::cout << "Running job '" << currentJob.getName() 
                      << "' for " << currentJob.getLength() << " time slices." << std::endl;
            
            currentJob.setLength(currentJob.getLength() - 1);
            if (!currentJob.jobDone()) {//jobQueue.removeRoot(); // job is done 
               jobQueue.insert(currentJob); 
            }
            // After processing, the job is completed and not added back to the queue
        } else {
            std::cout << "No new job this slice." << std::endl;
        }
    }

    // Check if there are any jobs in the queue
    bool hasJobs() const {
        return !jobQueue.empty();
    }

    // Print all jobs in the queue
    void printJobs() const {
        if (jobQueue.empty()) {
            std::cout << "No jobs in the queue." << std::endl;
            return;
        }

        // Create a temporary priority queue copy for traversal
        auto tempQueue = jobQueue;
        std::cout << "Jobs in the queue:" << std::endl;
        while (!tempQueue.empty()) {
            Job job = tempQueue.root();      // Get the job at the root
            tempQueue.removeRoot();          // Remove the root from the temporary queue

            // Print the job's details
            std::cout << "Job Name: " << job.getName()
                      << ", Duration: " << job.getLength()
                      << ", Priority: " << job.getPriority()
                      << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif // SCHEDULER_HPP