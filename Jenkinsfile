pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        stage('Build') {
            steps {
                sh 'make re'
            }
        }
        stage('Test') {
            steps {
                // sh 'valgrind ./webserv ./config/default.conf'
                // sh 'cppcheck --enable=all --force --quiet .'
                sh 'docker-compose up --build'
            }
        }
        // stage('Lint') {
        //     steps {
        //         sh 'your_linter_command'
        //     }
        // }
        // stage('Dockerize') {
        //     steps {
        //         sh 'docker build -t your_image_name .'
        //     }
        // }
    }
}
