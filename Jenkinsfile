
pipeline {
    agent any
    
    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        stage('Install Dependencies') {
            steps {
                sh '''
                    sudo apt-get update
                    sudo apt-get install -y clang-format cppcheck make
                '''
            }
        }
        stage('Lint') {
            steps {
                script {
                    def lintResult = sh(script: 'cppcheck --enable=all --error-exitcode=1 .', returnStatus: true)
                    if (lintResult != 0) {
                        error "Linting errors found"
                    }
                }
            }
        }
        stage('Format') {
            steps {
                script {
                    sh 'find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i'
                    def gitDiff = sh(script: 'git diff --exit-code', returnStatus: true)
                    if (gitDiff != 0) {
                        error "Formatting errors found"
                    }
                }
            }
        }
        stage('Build') {
            steps {
                sh 'make re'
            }
        }
    }

    post {
        always {
            junit '**/build/test-results/*.xml'
        }
        success {
            echo 'Build succeeded'
        }
        failure {
            echo 'Build failed'
        }
    }
}
