FROM ubuntu:latest
WORKDIR /app
COPY dist /app
CMD ["./executable"]
