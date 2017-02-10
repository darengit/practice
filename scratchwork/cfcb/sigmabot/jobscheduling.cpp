std::vector<int> jobScheduling(std::vector<int> requestTime, std::vector<int> jobProcess, int timeFromStart) {
    int next=0, scheduledtime=0;
    vector<int> jobqueue;
    
    while(!jobqueue.empty() || next<requestTime.size()) {
        if(jobqueue.empty()) {

            if(requestTime[next]>=timeFromStart)
                return jobqueue;
            
            jobqueue.push_back(next++);
        } else if (next == requestTime.size()) { // all requests are at least in job queue
            scheduledtime = max(scheduledtime,requestTime[jobqueue[0]]);
            
            if(scheduledtime>=timeFromStart)
                return jobqueue;
            
            scheduledtime += jobProcess[jobqueue[0]];
            jobqueue.erase(jobqueue.begin());
        } else { // there are jobs in jobqueue as well as requests coming in
            scheduledtime = max(scheduledtime,requestTime[jobqueue[0]]);
            if(scheduledtime < requestTime[next]) { // process a job queue job
                
                if(scheduledtime>=timeFromStart)
                    return jobqueue;
            
                scheduledtime += jobProcess[jobqueue[0]];
                jobqueue.erase(jobqueue.begin());
            } else { // add a request into jobqueue
 
                if(requestTime[next]>timeFromStart)
                    return jobqueue;
            
                jobqueue.push_back(next++);
                for(int j=jobqueue.size()-2; j>=0; --j) {
                    if(jobProcess[jobqueue[j+1]] < jobProcess[jobqueue[j]]) {
                        swap(jobqueue[j],jobqueue[j+1]);
                    }
                }
            }
        }
    }
    
    return jobqueue;
}

