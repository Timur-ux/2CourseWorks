#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int workersCount) : isStopped(false) {
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&queue_mutex, NULL);
    
    for(int i = 0; i < workersCount; ++i) {
        workers.push_back(pthread_t());
        pthread_create(&workers[i], NULL, &workerRun, this);
    }
}

void ThreadPool::addTask(Task &&task) {
    pthread_mutex_lock(&queue_mutex);

    tasks.push(task);

    pthread_mutex_unlock(&queue_mutex);

    pthread_cond_signal(&cond);
}

Task ThreadPool::getTask()
{
    Task task = tasks.front();
    tasks.pop();
    
    return task;
}

ThreadPool::~ThreadPool() {
    closeAll();

    isStopped = true;

    pthread_cond_broadcast(&cond);

    for(pthread_t worker : workers) {
        pthread_join(worker, NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&queue_mutex);
}

void ThreadPool::closeAll()
{
    while(counter > 0 or not tasks.empty()) {
        pthread_cond_broadcast(&cond);
    }
}
bool ThreadPool::isTasksEmpty() {
    bool result = tasks.empty();
    
    return result;
}
void *workerRun(void *_pool)
{
    ThreadPool * pool = static_cast<ThreadPool*>(_pool);
    while(true) {

        pthread_mutex_lock(&pool->queue_mutex);
        while(not pool->isStopped and pool->isTasksEmpty()) {
            pthread_cond_wait(&pool->cond, &pool->queue_mutex);
        }
        
        if(pool->isStopped) {
            pthread_mutex_unlock(&pool->queue_mutex);
            return NULL;
        }
        ++counter;
        Task task = pool->getTask();

        pthread_mutex_unlock(&pool->queue_mutex);
        task();
        --counter;
    }
    return NULL;
}

void Task::operator()() {
    func(workerData);
}
