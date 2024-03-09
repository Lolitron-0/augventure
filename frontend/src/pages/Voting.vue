<template>
  <div class="back">
    <div class="profile">
      <div class="container-for-navbar">
        <img :src="events.picture_url" alt="" class="ellipse-logo"/>
        <div class="title-event">{{ events.title }}</div>
        <i class='bx bx-dots-horizontal-rounded icon-dots' id="dots-icon" v-if="show" @click="Show" key="dots"></i>
        <div class="description-event" v-else>{{ events.description }}</div>
      </div>

      <div class="container-for-blocks-profile">
        <div class="sprint-history">
          <div class="title-for-sprint-history">Sprint history</div>
          <div class="container-for-sprints">
            <!-- здесь будет дерево спринтов -->
          </div>
        </div>

        <div class="voting-chat">
          <div class="title-for-voting-chat" v-if="events.state === 'in_progress'">Voting in progress...</div>
          <div class="title-for-voting-chat" v-else>Voting results</div>

          <div class="chat-messages" ref="messageContainer">
            <div class="message-container" >
              <div
                  v-for="(message, index) in messages"
                  :key="index"
                  :class="getMessageClasses(message)"
              >
                <div class="message-content">
                  <div class="username">{{ message.username }}</div>
                  <div class="text-with-avatar">
                    <img v-if="message.avatar !== this.user.pfp_url" :src="message.avatar" alt="" class="avatar"/>
                    <div class="message-text">{{ message.content }}</div>
                    <img v-if="message.avatar === this.user.pfp_url" :src="message.avatar" alt="" class="avatar"/>
                  </div>
                </div>
              </div>
            </div>
          </div>

          <form class="form-send-message" @submit.prevent="SendMessage">
            <input
                type="text"
                v-model="inputMessage"
                class="input-for-send-message"
                placeholder="Message"
            >
            <button type="submit" class="send-btn">
              <i class='bx bx-send icon-send' @click="SendMessage"></i>
            </button>
          </form>

        </div>
      </div>
    </div>
  </div>
</template>

<script>
import MyButton from "@/components/UI/MyButton.vue";
import { ref, push, onValue } from "firebase/database";
import { db } from "@/pages/db";
export default {
  components: { MyButton },
  data() {
    const user = JSON.parse(localStorage.getItem('user'));
    return {
      user: user,
      events: {},
      descriptionVisible: false,
      show: true,
      inputMessage: "",
      messages: {},
      ID: this.$route.params.id
    }
  },
  async beforeMount() {
    try {
      const ev = await this.$api.events.getOne(this.ID);
      this.events = ev.data.event

    } catch (error) {
      console.log('failed:', error);
    }
  },
  methods: {
    getMessageClasses(message) {
      return {
        'message-right': message.username === this.user.username,
        'message-left': message.username !== this.user.username,
      };
    },
    toggleDescription() {
      this.descriptionVisible = !this.descriptionVisible;
    },
    Show() {
      this.show = !this.show;
    },
    SendMessage() {
      const messagesRef = ref(db, "message_" + this.ID);

      if (this.inputMessage === "" || this.inputMessage === null) {
        return;
      }

      const message = {
        username: this.user.username,
        content: this.inputMessage,
        avatar: this.user.pfp_url
      }

      push(messagesRef, message);
      this.inputMessage = "";

    }
  },
  async mounted() {
    try {

      const messagesRef = ref(db, "message_" + this.ID);

      onValue(messagesRef, (snapshot) => {
        const data = snapshot.val();
        if (data) {
          this.messages = Object.values(data);

          this.$nextTick(() => {
            const messageContainer = this.$refs.messageContainer;
            if (messageContainer) {
              messageContainer.scrollTop = messageContainer.scrollHeight;
            }
          });
        }
      });
    } catch (error) {
      console.log("Failed to fetch messages:", error);
    }
  },
}
</script>

<style scoped>
@import "@/styles.css";

.back {
  background-color: var(--background-app-color);
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 24px 5%;
  overflow-y: auto;
  overflow-x: hidden;
}

.profile {
  position: absolute;
  width: 85vw;
  height: 91vh;
}

.container-for-blocks-profile {
  position: relative;
  width: 100%;
  height: 83vh;
}

.sprint-history {
  position: absolute;
  left: 0;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 25%;
  height: 80vh;
}

.voting-chat {
  position: absolute;
  left: 28%;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 72%;
  height: 80vh;
}

.container-for-navbar {
  top: 0;
  width: 100%;
  position: relative;
  height: 50px;
  display: flex;
  justify-content: left;
  align-items: center;
  gap: 30px;
  border-bottom: 1px solid var(--border-light-gray-color);
  padding: 5px 10px;
  color: #cfcfcf;
  margin-bottom: 15px;
}

.title-for-sprint-history {
  color: var(--text-wight-color);
  width: 100%;
  height: 40px;
  font-size: 18px;
  position: absolute;
  align-items: center;
  justify-content: center;
  background-color: var(--navbar-color);
  border-bottom: 1px solid var(--border-light-gray-color);
  display: flex;
  border-top-left-radius: 5px;
  border-top-right-radius: 5px;
}

.title-for-voting-chat {
  color: var(--text-wight-color);
  width: 100%;
  font-size: 18px;
  height: 40px;
  position: absolute;
  display: flex;
  align-items: center;
  justify-content: center;
  background-color: var(--navbar-color);
  border-bottom: 1px solid var(--border-light-gray-color);
  border-top-left-radius: 5px;
  border-top-right-radius: 5px;
}

.ellipse-logo {
  height: 90%;
  border: 1px solid #858585;
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 50%;
  aspect-ratio: 1;
}

.title-event {
  font-size: 18px;
}

.title-event::first-letter {
  text-transform: uppercase;
}

.description-event {
}

.icon-dots {
  font-size: 22px;
}

.form-send-message {
  position: absolute;
  width: 100%;
  height: 40px;
  border-top: 2px solid var(--border-light-gray-color);
  background-color: var(--background-app-color);
  display: flex;
  bottom: 0;
}

.input-for-send-message {
  width: calc(100% - 60px);
  font-size: 16px;
  color: var(--text-wight-color);
  height: 38px;
  background-color: var(--background-app-color);
  left: 0;
  border: none;
  padding: 0 5px 0 5px;
  justify-content: center;
  align-items: center;
  margin-right: 5px;
  border-radius: 5px;
  resize: vertical;
}

.send-btn {
  right: 10px;
  position: absolute;
  justify-content: center;
  align-items: center;
  border: none;
  background: none;
  cursor: pointer;
}

.icon-send {
  position: absolute;
  font-size: 35px;
  color: var(--text-wight-color);
  right: 10px;
  justify-content: center;
  align-items: center;
  transition: .5s;
  cursor: pointer;
}

.icon-send:hover {
  color: var(--text-turquoise-color);
}

.chat-messages {
  height: calc(100% - 80px);
  width: 100%;
  top: 40px;
  position: absolute;
  overflow-y: auto;
}

.chat-messages::-webkit-scrollbar {
  width: 0;  /* Ширина полосы прокрутки */
  height: 0; /* Высота полосы прокрутки (горизонтальная полоса) */
}

.message-container {
  padding: 10px;
  //flex: 1;
}

.avatar {
  width: 30px;
  height: 30px;
  border-radius: 50%;
  overflow: hidden;
  margin-left: 10px;
}

.message-content {
  display: flex;
  flex-direction: column;
}

.username {
  color: grey;
  margin-bottom: 5px;
}

.text-with-avatar {
  display: flex;
  align-items: flex-start;
}

.message-text {
  padding: 8px;
  border-radius: 10px;
  color: black;
  word-wrap: break-word;
  //overflow-wrap: break-word;
  word-break: break-all;
}

.message-right {
  display: flex;
  justify-content: flex-end;
  margin-bottom: 10px;
}

.message-left {
  display: flex;
  justify-content: flex-start;
  margin-bottom: 10px;
}

.message-right .avatar {
  order: 2;
  margin-left: 10px;
}

.message-left .avatar {
  order: 0;
  margin-right: 10px;
}

.message-right .message-text {
  background-color: #2ecc71;
  margin-left: 10px;
}

.message-left .message-text {
  background-color: #ffffff;
  margin-right: 10px;
}

.username.message-right {
  order: 1;
}

.username.message-left {
  order: -1;
}
</style>