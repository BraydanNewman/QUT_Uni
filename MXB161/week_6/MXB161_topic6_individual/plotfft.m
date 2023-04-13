function plotfft(y, Fs, varargin)
% PLOTFFT  Plot relative signal amplitude vs frequency

abs_fft_y = abs(fft(y));
n = length(y);
f = (0:n-1)*(Fs/n);
scaled_fft = abs_fft_y / max(abs_fft_y);
plot(f, scaled_fft, varargin{:})
xlim([0, Fs/2])
xlabel('Frequency (Hz)')
ylabel('Relative amplitude')