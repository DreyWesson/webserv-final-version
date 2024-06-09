pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        stage('Lint') {
            steps {
                script {
                    def lintResult = sh(script: 'npm run lint', returnStatus: true)
                    if (lintResult != 0) {
                        error "Linting errors found"
                    }
                }
            }
        }
        stage('Format') {
            steps {
                script {
                    sh 'npm run format'
                    def gitDiff = sh(script: 'git diff --exit-code', returnStatus: true)
                    if (gitDiff != 0) {
                        error "Formatting errors found"
                    }
                }
            }
        }
        // stage('Build') {
        //     steps {
        //         sh 'npm run build'
        //     }
        // }
    }

    post {
        // always {
        //     junit '**/build/test-results/*.xml'
        // }
        success {
            echo 'Build succeeded'
        }
        failure {
            echo 'Build failed'
        }
    }
}
