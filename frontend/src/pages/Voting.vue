<template>
  <div class="back">
    <div class="profile">
      <div class="container_for_navbar">
        <img :src="events.picture_url" alt="" class="ellipse_logo"/>
        <div class="title_event">{{ events.title }}</div>
        <i class='bx bx-dots-horizontal-rounded icon_dotes' id="dotes-icon" v-if="show" @click="Show" key="dotes"></i>
        <div class="description_event" v-else>{{ events.description }}</div>
      </div>

      <div class="container_for_blocks_profile">
        <div class="sprint_history">
          <div class="title_for_sprint_history">Sprint history</div>
          <div class="container_for_sprints">
<!--            здесь будет дерево спринтов-->
          </div>
        </div>

        <div class="voting_chat">
          <div class="title_for_voting_chat" v-if="events.state === 'in_progress'">Voting in progress...</div>
          <div class="title_for_voting_chat" v-else>Voting results</div>

          <div class="chat_messages">
            <div
                v-for="message in this.messages"
                :key="message.id"
                :class="((message.username === this.user.username) ? 'message current_user' : 'message')">
              <div class="message_inner">
                <div class="username">{{ message.username }}</div>
                <div class="content">{{ message.content }}</div>
              </div>
            </div>
          </div>

          <form class="form_send_messege" @submit.prevent="SendMessage">

            <input type="text" v-model="inputMessage" class="input_from_for_send_messege" placeholder="Messege">
            <input type="submit" class="send_btn" value="Send">
<!--            <i class='bx bx-send icon_send' @click=""></i>-->
<!--            <my-button type="submit" class="send_btn"></my-button>-->
          </form>

        </div>
      </div>
    </div>
  </div>
</template>

<script>
import MyButton from "@/components/UI/MyButton.vue";
import { ref, push } from "firebase/database";
import { db, onSnapshot } from "@/pages/db";
export default {
  components: {MyButton},
  data() {
    const user = JSON.parse(localStorage.getItem('user'));
    return {
      user: user,
      events: {},
      descriptionVisible: false,
      show: true,
      inputMessage: "",
      messages: {}
    }
  },
  async beforeMount() {
    try {
      const ID = this.$route.params.id;
      const ev = await this.$api.events.getOne(ID);
      this.events = ev.data.event

    } catch (error) {
      console.log('failed:', error);
    }
  },
  methods: {
    toggleDescription() {
      this.descriptionVisible = !this.descriptionVisible;
    },
    Show() {
      this.show = !this.show;
    },
    SendMessage() {
      const messagesRef = ref(db, "messages");

      if (this.inputMessage === "" || this.inputMessage === null) {
        return;
      }

      const message = {
        username: this.user.username,
        content: this.inputMessage
      }

      push(messagesRef, message);
      this.inputMessage = "";
    }
  },
  mounted() {
    const messagesRef = ref(db, "messages");

    onSnapshot(messagesRef, (snapshot) => {
      const data = snapshot.val();
      console.log('data', data)
      let messages = {};

      Object.keys(data).forEach(key => {
        messages[key] = {
          id: key,
          username: data[key].username,
          content: data[key].content
        };
      });

      this.messages = messages;
    });
  }

}
</script>

<style scoped>
@import "@/styles.css";


hr {
  margin-top: 5px;
  background-color: var(--border-light-gray-color);
  padding: .3px;
  border: var(--border-light-gray-color);
}

.back {
  /* background-color: #0d1117; */
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
  //border: 1px solid red;
  width: 85vw;
  height: 100%;
}
.container_for_blocks_profile {
  position: relative;
  width: 100%;
  height: 100%;
}
.sprint_history {
  position: absolute;
  left: 0;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 25%;
  height: 80vh;
  //padding: 2%;
}

.voting_chat {
  position: absolute;
  left: 28%;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 72%;
  height: 80vh;
  //padding: 0 10px 10px 10px;
}

.container_for_navbar {
  //border: 1px solid red;
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

.title_for_sprint_history {
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

.title_for_voting_chat {
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

.ellipse_logo {
  height: 90%;
  border: 1px solid #858585;
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 50%;
  aspect-ratio: 1;
}

.title_event {
  font-size: 18px;
}

.title_event::first-letter {
  text-transform: uppercase;
}

.description_event {

}

.icon_dotes {
  font-size: 22px;
}

.form_send_messege {
  position: absolute;
  width: 100%;
  height: 40px;
  border-top: 2px solid var(--border-light-gray-color);
  background-color: var(--background-app-color);
  display: flex;
  bottom: 0;
}

.input_from_for_send_messege {
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
}

.send_btn {
  width: 35px;
  height: 35px;
  right: 0;
  position: absolute;
  justify-content: center;
  align-items: center;
  border: none;
  //color: var(--text-wight-color);
}
.icon_send {
  position: absolute;
  font-size: 35px;
  //height: 35px;
  color: var(--text-wight-color);
  right: 10px;
  justify-content: center;
  align-items: center;
  transition: .5s;
  cursor: pointer;
  //background-color: #cfcfcf;
}

.icon_send:hover {
  color: var(--text-turquoise-color);
}




.chat_messages {
  position: absolute;
  width: 100%;
  top: 40px;
  height: calc(100% - 40px);
  background-color: var(--background-app-color);
  padding: 30px;
  //flex: 1 1 100%;
}

.chat_messages .message {
  display: flex;
  margin-bottom: 15px;
}

.chat_messages .message .message_inner .username {
  color: #888;
  font-size: 16px;
  margin-bottom: 5px;
  padding: 0 15px;
}

.chat_messages .message .message_inner .content {
  display: inline-block;
  padding: 10px 20px;
  background-color: #f3f3f3;
  border-radius: 999px;
  color: #333;
  font-size: 18px;
  line-height: 1.2em;
  text-align: left;
}

.chat_messages .message.current_user {
  margin-top: 30px;
  justify-content: flex-end;
  text-align: right;
}

.chat_messages .message.current_user .message_inner {
  max-width: 75%;
}

.chat_messages .message.current_user .message_inner .content {
  color: #fff;
  font-weight: 600;
  background-color: #ea526f;
}
</style>