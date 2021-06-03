#pragma once

#include <chrono>
#include <string>
#include <boost/optional/optional.hpp>
#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <boost/timer.hpp>
#include <boost/asio.hpp>
struct Timer {
  using Clock = std::chrono::high_resolution_clock;

  static long long GetCurrentTimeInMilliseconds();

  // Creates a new timer. A timer is always running.
  Timer();

  // Returns elapsed microseconds.
  long long ElapsedMicroseconds() const;
  // Returns elapsed microseconds and restarts/resets the timer.
  long long ElapsedMicrosecondsAndReset();
  // Restart/reset the timer.
  void Reset();
  // Resets timer and prints a message like "<foo> took 5ms"
  void ResetAndPrint(const std::string& message);
  // Pause the timer.
  void Pause();
  // Resume the timer after it has been paused.
  void Resume();

  // Raw start time.
  boost::optional<std::chrono::time_point<Clock>> start_;
  // Elapsed time.
  long long elapsed_ = 0;
};

struct ScopedPerfTimer {
  ScopedPerfTimer(const std::string& message);
  ~ScopedPerfTimer();

  Timer timer_;
  std::string message_;
};

template<typename Duration = boost::posix_time::milliseconds>
class ATimer
{
public:
    ATimer() : m_timer(m_ios, Duration(0)), m_isSingleShot(true)
    {
	    
    }
    ~ATimer()
    {
        stop();
    }

    void start(unsigned int duration)
    {
    	
        if (m_ios.stopped())
        {
            return;
        }

        m_isActive = true;
        m_duration = duration;
        m_timer.expires_at(m_timer.expires_at() + Duration(m_duration));
        m_func = [this]
        {
            m_timer.async_wait([this](const boost::system::error_code&)
                {
                    for (auto& func : m_funcVec)
                    {
                        func();
                    }

                    if (!isSingleShot())
                    {
                        m_timer.expires_at(m_timer.expires_at() + Duration(m_duration));
                        m_func();
                    }
                });
        };

        m_func();
        m_thread = std::thread([this] { m_ios.run(); });
        
    }

    void stop()
    {
        m_ios.stop();
        if (m_thread.joinable())
        {
            m_thread.join();
        }
        m_isActive = false;
    }

    void bind(const std::function<void()>& func)
    {
        m_funcVec.emplace_back(func);
    }

    void setSingleShot(bool isSingleShot)
    {
        m_isSingleShot.store(isSingleShot,std::memory_order_relaxed);
    }

    bool isSingleShot() const
    {
        return    m_isSingleShot.load(std::memory_order_relaxed);
    }

    bool isActive() const
    {
        return m_isActive;
    }

private:
  
    boost::asio::io_service m_ios;
    boost::asio::deadline_timer m_timer;
    std::function<void()> m_func = nullptr;
    std::vector<std::function<void()>> m_funcVec;
    std::thread m_thread;
    unsigned int m_duration = 0;
    std::atomic<bool> m_isSingleShot;
    bool m_isActive = false;
};
