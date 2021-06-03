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
class SimpleTimer
{
public:
    SimpleTimer(unsigned int duration,const std::function<void()>& _call_back)
	:is_running_(true), call_back(_call_back), _deadline_timer(_ios, Duration(duration))
    {
        _deadline_timer.async_wait([&](const boost::system::error_code& e)
        {
            if (e.value() == boost::asio::error::operation_aborted)
            {
                return;
            }
            if(is_running_.load(std::memory_order_relaxed))
            {
                call_back();
            }

        });
        _thread = std::thread([this] { _ios.run(); });
    }
    ~SimpleTimer()
    {
        Stop();
    }
    void Stop()
    {
        is_running_.store(false, std::memory_order_relaxed);
        _ios.stop();
        if (_thread.joinable())
        {
            _thread.join();
        }
    }
private:
    std::function<void()> call_back;
    std::atomic_bool is_running_;
    boost::asio::io_service _ios;
    boost::asio::deadline_timer _deadline_timer;
    std::thread _thread;

  
};
